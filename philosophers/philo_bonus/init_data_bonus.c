/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:52 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:40:08 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Initializes philosopher structures within the table.
 * Sets default values and associates each philosopher with the table.
 * Also records the simulation start time.
 *
 * @param table Pointer to the simulation table.
 */
static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i;
		table->philos[i].n_eat = 0;
		table->philos[i].max_eat = table->max_eat;
		table->philos[i].last_m = 0;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].philo_nbr = table->philo_nbr;
		i++;
	}
	table->start_simulation = gettime_b(MILLISECOND);
}

/**
 * Initializes shared semaphores and allocates memory for philosopher and PID arrays.
 * Prepares synchronization primitives and philosopher data before simulation start.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on failure with error message printed.
 */
long	init_data_bonus(t_table *table)
{
	int	i;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/to_write");
	sem_unlink("/end_sim");
	sem_unlink("/last_meal");
	sem_unlink("/death");
	sem_unlink("/all_eat");
	table->end_simulation = sem_open("/end_sim", O_CREAT, 0666, 0);
	table->all_eat = sem_open("all_eat", O_CREAT, 0666, 0);
	table->forks = sem_open("/forks", O_CREAT, 0666, table->philo_nbr);
	table->to_write = sem_open("/to_write", O_CREAT, 0666, 1);
	table->death = sem_open("/death", O_CREAT, 0666, 1);
	table->last_meal = sem_open("/last_meal", O_CREAT, 0666, 1);
	if (table->forks == SEM_FAILED || table->to_write == SEM_FAILED
		|| table->end_simulation == SEM_FAILED || table->last_meal == SEM_FAILED
		|| table->death == SEM_FAILED || table->all_eat == SEM_FAILED)
		return (error_ex("Error to create sem_t value"), -1);
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	table->pids = malloc(sizeof(pid_t) * table->philo_nbr);
	if (!table->pids || !table->philos)
		return (error_ex("Error malloc"), -1);
	init_philos(table);
	return (0);
}
