/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:13:22 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:26:09 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Thread-safe setter for a boolean variable.
 * Locks the mutex before writing and unlocks after.
 *
 * @param mutex Pointer to the mutex protecting the boolean.
 * @param dest Pointer to the boolean variable to set.
 * @param value Boolean value to assign.
 */
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/**
 * Thread-safe getter for a boolean variable.
 * Locks the mutex before reading and unlocks after.
 *
 * @param mutex Pointer to the mutex protecting the boolean.
 * @param dest Pointer to the boolean variable to read.
 * @return The current value of the boolean variable.
 */
bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *dest;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * Thread-safe setter for a long integer variable.
 * Locks the mutex before writing and unlocks after.
 *
 * @param mutex Pointer to the mutex protecting the long variable.
 * @param dest Pointer to the long variable to set.
 * @param value Long value to assign.
 */
void	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

/**
 * Thread-safe getter for a long integer variable.
 * Locks the mutex before reading and unlocks after.
 *
 * @param mutex Pointer to the mutex protecting the long variable.
 * @param dest Pointer to the long variable to read.
 * @return The current value of the long variable.
 */
long	get_long(t_mtx *mutex, long *dest)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *dest;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/**
 * Checks if the simulation has finished.
 * Thread-safe read of the 'end_simulation' flag in the table.
 *
 * @param table Pointer to the simulation table.
 * @return true if simulation ended, false otherwise.
 */
bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_simulation));
}
