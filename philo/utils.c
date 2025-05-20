/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:45 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/26 19:12:02 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

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

void	error_ex(const char *error)
{
	printf("%s", error);
}

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

void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

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
