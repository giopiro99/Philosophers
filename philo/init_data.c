/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:14:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:32:05 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Assigns forks to a philosopher based on their ID.
 * Ensures even-numbered philosophers pick up the forks in a reversed order to avoid deadlock.
 *
 * @param philo Pointer to the philosopher.
 * @param forks Array of forks.
 * @param i Index of the philosopher in the array.
 */
static void	assign_fork(t_philo *philo, t_fork *forks, int i)
{
	philo->first_fork = &forks[(i + 1) % philo->table->philo_nbr];
	philo->second_fork = &forks[i];
	if ((philo->philo_id % 2) == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo->table->philo_nbr];
	}
}

/**
 * Initializes each philosopher in the table.
 * Sets initial states, IDs, associates forks, and initializes mutexes.
 * Also sets the simulation start time.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on failure.
 */
static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = NULL;
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->full = false;
		philo->philo_id = i;
		philo->table = table;
		philo->meal_counter = 0;
		if (pthread_mutex_init(&table->philos[i].philo_mutex, NULL) < 0)
			return (-1);
		assign_fork(philo, table->forks, i);
		i++;
	}
	table->start_simulation = gettime(MILLISECOND);
	return (0);
}

/**
 * Initializes simulation data including philosophers, forks, and mutexes.
 * Allocates memory and sets initial state variables.
 *
 * @param table Pointer to the simulation table.
 * @return 0 on success, -1 on failure.
 */
long	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (error_ex("Malloc error"), -1);
	table->end_simulation = false;
	table->threads_ready = false;
	table->threads_running = 0;
	if (pthread_mutex_init(&table->table_mtx, NULL) < 0
		|| pthread_mutex_init(&table->write_mutex, NULL) < 0)
		return (error_ex("Error with init mutex"), -1);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (error_ex("Error with forks"), -1);
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) < 0)
			return (error_ex("Error with fork mutex"), -1);
		table->forks[i].fork_id = i;
		i++;
	}
	if (philo_init(table) < 0)
		return (error_ex("Error with the philos init"), -1);
	return (0);
}
