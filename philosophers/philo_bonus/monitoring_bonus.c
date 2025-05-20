/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:07:52 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:38:46 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Monitor thread that checks if a philosopher has died.
 * If the time since the last meal exceeds the time to die,
 * it signals death, prints status, and ends the simulation.
 *
 * @param arg Pointer to the philosopher structure.
 * @return NULL (never returns due to exit on death).
 */
void	*monitor_dinner(void *arg)
{
	long	last_meal;
	t_philo	*philo;

	last_meal = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		last_meal = gettime_b(MILLISECOND)
			- get_long(philo->table->last_meal, &philo->last_m);
		if (last_meal >= (philo->time_to_die / 1e3))
		{
			sem_wait(philo->table->death);
			write_status(philo, DIE,gettime_b(MILLISECOND));
			sem_wait(philo->table->to_write);
			sem_post(philo->table->end_simulation);
			exit(0);
		}
		usleep(100);
	}
}

/**
 * Parent process waits for the simulation to end, then kills all philosopher
 * child processes and the monitor process, and waits for their termination.
 *
 * @param table Pointer to the simulation table.
 */
static void	parent_process(t_table *table)
{
	int	i;

	i = 0;
	sem_wait(table->end_simulation);
	while (i < table->philo_nbr)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
	if (kill(table->monitor_pid, 0) == 0)
		kill(table->monitor_pid, SIGKILL);
	i = 0;
	while (i < table->philo_nbr)
	{
		waitpid(table->pids[i], NULL, 0);
		i++;
	}
	waitpid(table->monitor_pid, NULL, 0);
}

/**
 * Creates a monitor child process that waits until all philosophers have eaten
 * the required number of times. Then signals the end of the simulation.
 * The parent process handles process cleanup.
 *
 * @param table Pointer to the simulation table.
 */
static void	monitor_process(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	table->monitor_pid = pid;
	if (pid == 0)
	{
		while (i < table->philo_nbr)
		{
			sem_wait(table->all_eat);
			i++;
		}
		sem_post(table->end_simulation);
		exit(0);
	}
	if (pid != 0)
		parent_process(table);
}

/**
 * Starts the philosopher processes and the monitor process.
 * Each philosopher runs its routine in a separate process.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on fork error.
 */
long	start_dinner_bonus(t_table *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	while (i < table->philo_nbr)
	{
		pid = fork();
		if (pid == -1)
			return (error_ex("Error to fork a process\n"), -1);
		if (pid == 0)
		{
			start_routine(&table->philos[i]);
			exit (0);
		}
		if (pid != 0)
		{
			table->pids[i] = pid;
			i++;
		}
	}
	monitor_process(table);
	return (0);
}
