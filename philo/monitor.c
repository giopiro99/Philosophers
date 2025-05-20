/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:01:06 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/27 10:38:09 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(t_philo *philo)
{
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->threads_running);
	to_write_status(philo, TAKE_FIRST, gettime(MILLISECOND));
	while (!simulation_finish(philo->table))
		usleep(200);
	return (NULL);
}

bool	philo_die(t_philo *philo)
{
	long	t_elapsed;
	long	t_last_meal;

	t_elapsed = 0;
	t_last_meal = get_long(&philo->philo_mutex, &philo->last_meal_time);
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	t_elapsed = gettime(MILLISECOND) - t_last_meal;
	if (t_elapsed > (philo->table->time_to_die / 1000))
		return (true);
	return (false);
}

void	*monitor_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (!all_threads_running(&table->table_mtx,
			&table->threads_running, table->philo_nbr))
		;
	while (!simulation_finish(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finish(table))
		{
			if (philo_die(&table->philos[i]))
			{
				to_write_status(&table->philos[i], DIE, gettime(MILLISECOND));
				set_bool(&table->table_mtx, &table->end_simulation, true);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
