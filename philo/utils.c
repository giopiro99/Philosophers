/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:45 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:24:25 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

/**
 * Prints the current status of a philosopher in a thread-safe way.
 * It locks the write mutex to avoid mixed output and only prints if simulation is not finished.
 *
 * @param philo Pointer to the philosopher struct.
 * @param status The current status of the philosopher (e.g. THINK, EAT, DIE).
 * @param time Current timestamp in milliseconds.
 */
void	to_write_status(t_philo *philo, t_write status, long time)
{
	long	start_simul;

	start_simul = get_long(&philo->philo_mutex, &philo->table->start_simulation);
	pthread_mutex_lock(&philo->table->write_mutex);
	if (status == TAKE_FIRST && !simulation_finish(philo->table))
		printf("%lu philo %d has taken a fork\n",(time - start_simul), philo->philo_id);
	else if (status == TAKE_SECOND && !simulation_finish(philo->table))
		printf("%lu philo %d has taken a fork\n", (time - start_simul),philo->philo_id);
	else if (status == DIE && !simulation_finish(philo->table))
		printf("%lu philo %d died\n", (time - start_simul), philo->philo_id);
	else if (status == EAT && !simulation_finish(philo->table))
		printf("%lu philo %d is eating\n", (time - start_simul), philo->philo_id);
	else if (status == SLEEP && !simulation_finish(philo->table))
		printf("%lu philo %d is sleeping\n",(time - start_simul), philo->philo_id);
	else if (status == THINK && !simulation_finish(philo->table))
		printf("%lu philo %d is thinking\n",(time - start_simul), philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

/**
 * Prints an error message to standard output.
 *
 * @param error The error message string.
 */
void	error_ex(const char *error)
{
	printf("%s", error);
}

/**
 * Frees all allocated resources associated with the simulation.
 * Destroys all mutexes and frees allocated arrays and the table itself.
 *
 * @param table Pointer to the simulation table struct.
 */
void	free_all(t_table *table)
{
	int	i;

	i = 0;
	if (!table || !table->philos)
		return ;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->write_mutex);
	free(table->philos);
	free(table->forks);
	free(table);
}

/**
 * Safely increments a long integer protected by a mutex.
 *
 * @param mutex Pointer to the mutex protecting the value.
 * @param value Pointer to the long integer to increment.
 */
void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

/**
 * Checks if all threads are running by comparing a counter to the total number of philosophers.
 * The access is protected by a mutex.
 *
 * @param mutex Mutex protecting the thread counter.
 * @param thread Pointer to the counter variable.
 * @param philo_nbr Total number of philosopher threads expected.
 * @return true if all threads are running, false otherwise.
 */
bool	all_threads_running(t_mtx *mutex, long *thread, long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if ((*thread) == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}
