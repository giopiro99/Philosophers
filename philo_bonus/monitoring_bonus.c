/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:07:52 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/27 11:18:15 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <signal.h>

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
