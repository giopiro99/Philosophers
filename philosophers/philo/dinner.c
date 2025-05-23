/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:22:08 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:33:49 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Handles the thinking state of a philosopher.
 * For odd number of philosophers, introduces a calculated delay to avoid deadlock.
 * Optionally logs the thinking status.
 *
 * @param philo Pointer to the philosopher.
 * @param flag If true, writes thinking status to output.
 */
void	thinking(t_philo *philo, bool flag)
{
	long	t_think;

	t_think = 0;
	if (flag)
		to_write_status(philo, THINK, gettime(MILLISECOND));
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_think = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	usleep(t_think * 0.42);
}

/**
 * Philosopher attempts to eat by locking forks, updating state, and sleeping.
 * Manages meal count and marks philosopher as full if max meals reached.
 *
 * @param philo Pointer to the philosopher.
 */
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	to_write_status(philo, TAKE_FIRST, gettime(MILLISECOND));
	pthread_mutex_lock(&philo->second_fork->fork);
	to_write_status(philo, TAKE_SECOND,gettime(MILLISECOND));
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECOND));
	philo->meal_counter++;
	to_write_status(philo, EAT, gettime(MILLISECOND));
	usleep(philo->table->time_to_eat);
	if (philo->table->max_eat > 0
		&& philo->table->max_eat == philo->meal_counter)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/**
 * Main simulation loop for each philosopher.
 * Waits for all threads, then cycles through eating, sleeping, and thinking,
 * checking for death or fullness to end the simulation.
 *
 * @param philo Pointer to the philosopher.
 * @return Always returns NULL.
 */
void	*dinner_simulation(t_philo *philo)
{
	set_long(&philo->philo_mutex, &philo->table->start_simulation, gettime(MILLISECOND));
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running);
	desync(philo);
	while (!simulation_finish(philo->table))
	{
		if (philo_die(philo))
			break ;
		eat(philo);
		if (philo->full || philo_die(philo))
			break ;
		to_write_status(philo, SLEEP, gettime(MILLISECOND));
		usleep(philo->table->time_to_sleep);
		thinking(philo, true);
	}
	return (NULL);
}

/**
 * Special case handler for a lone philosopher.
 * Starts a single thread that runs the lone_philo routine.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on failure.
 */
static long	lone_dinner(t_table *table)
{
	if (pthread_create(&table->philos[0].thread_id,
			NULL, (void *)lone_philo, &table->philos[0]) < 0)
		return (-1);
	return (0);
}

/**
 * Starts the dinner simulation by creating philosopher threads and monitor thread.
 * Handles the special case of only one philosopher.
 * Joins all threads at the end and signals simulation end.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on failure.
 */
long	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_nbr == 1)
	{
		if (lone_dinner(table) == -1)
			return (-1);
	}
	else
	{
		while (i < table->philo_nbr)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL,
					(void *)dinner_simulation, &table->philos[i]) < 0)
				return (-1);
			i++;
		}
	}
	pthread_create(&table->monitor, NULL, (void *)monitor_dinner, table);
	i = 0;
	set_bool(&table->table_mtx, &table->threads_ready, true);
	while (i < table->philo_nbr)
		pthread_join(table->philos[i++].thread_id, NULL);
	set_bool(&table->table_mtx, &table->end_simulation, true);
	return (pthread_join(table->monitor, NULL), 0);
}
