/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:13:22 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/20 12:02:09 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *dest;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	get_long(t_mtx *mutex, long *dest)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *dest;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_simulation));
}
