/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:42:26 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/26 19:12:38 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	error_ex(const char *error)
{
	printf("%s", error);
}

void	free_all(t_table *table)
{
	if (table->forks)
		sem_close(table->forks);
	if (table->to_write)
		sem_close(table->to_write);
	if (table->end_simulation)
		sem_close(table->end_simulation);
	if (table->last_meal)
		sem_close(table->last_meal);
	if (table->death)
		sem_close(table->death);
	if (table->all_eat)
		sem_close(table->all_eat);
	if (table->philos)
		free(table->philos);
	if (table->pids)
		free(table->pids);
	if (table)
		free(table);
}

void	write_status(t_philo *philo, t_status status, long time)
{
	long	start_sim;

	start_sim = get_long(philo->table->to_write, &philo->table->start_simulation);
	sem_wait(philo->table->to_write);
	if (status == TAKE_FIRST)
		printf("%lu Philo %d has taken a fork\n",(time - start_sim), philo->philo_id);
	else if (status == TAKE_SECOND)
		printf("%lu Philo %d has taken a fork\n", (time - start_sim), philo->philo_id);
	else if (status == THINK)
		printf("%lu Philo %d is thinking\n", (time - start_sim), philo->philo_id);
	else if (status == SLEEP)
		printf("%lu Philo %d is sleeping\n", (time - start_sim), philo->philo_id);
	else if (status == DIE)
		printf("%lu Philo %d died\n", (time - start_sim), philo->philo_id);
	else if (status == EAT)
		printf("%lu Philo %d is eating\n", (time - start_sim), philo->philo_id);
	sem_post(philo->table->to_write);
}

long	gettime_b(t_time format)
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
