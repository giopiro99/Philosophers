/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:19:28 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:25:15 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Spinlock function that waits until all threads are ready.
 * Continuously checks the 'threads_ready' flag protected by a mutex.
 *
 * @param table Pointer to the shared simulation table.
 */
void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->threads_ready))
		;
}

/**
 * Gets the current time in the specified format.
 * Uses gettimeofday and returns time in milliseconds.
 *
 * @param format The time format to return (currently only MILLISECOND supported).
 * @return Current time in milliseconds on success, -1 on failure.
 */
long	gettime(t_time format)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_ex("error to get time"), -1);
	if (format == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (-1);
}

/**
 * Introduces desynchronization delay among philosophers to prevent deadlocks.
 * - For even number of philosophers, even IDs sleep a bit.
 * - For odd number, odd IDs think initially (non-blocking delay).
 *
 * @param philo Pointer to the philosopher struct.
 */
void	desync(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			usleep(50);
	}
	else
	{
		if (philo->philo_id % 2)
			thinking(philo, false);
	}
}
