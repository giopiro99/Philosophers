/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:19:28 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/20 12:16:44 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>
#include <unistd.h>
//spinlock to wait all threads
void	wait_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->threads_ready))
		;
}

long	gettime(t_time format)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_ex("error to get time"), -1);
	if (format == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (-1);
}

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
