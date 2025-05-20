/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:21:34 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:40:50 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Simulates the philosopher thinking state.
 * Only philosophers in an odd-numbered group think for a calculated time.
 * The thinking duration is adjusted based on eating and sleeping times.
 *
 * @param philo Pointer to the philosopher.
 * @param flag If true, prints the thinking status.
 */
void	thinking(t_philo *philo, bool flag)
{
	long	t_think;

	t_think = 0;
	if (philo->philo_nbr % 2 == 0)
		return ;
	else
	{
		t_think = (philo->time_to_eat * 2) - philo->time_to_sleep;
		if (t_think < 0)
			t_think = 0;
		if (flag)
			write_status(philo, THINK, gettime_b(MILLISECOND));
		usleep(t_think * 0.42);
	}
}

/**
 * Executes the eating routine for a philosopher.
 * The philosopher tries to pick up two forks (semaphores),
 * waits for the eating duration, updates last meal time,
 * then releases the forks.
 *
 * @param philo Pointer to the philosopher.
 */
void	eat_routine(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		usleep(150);
	sem_wait(philo->table->forks);
	write_status(philo, TAKE_FIRST, gettime_b(MILLISECOND));
	sem_wait(philo->table->forks);
	write_status(philo, TAKE_SECOND, gettime_b(MILLISECOND));
	usleep(philo->time_to_eat);
	set_long(philo->table->last_meal, &philo->last_m, gettime_b(MILLISECOND));
	write_status(philo, EAT, gettime_b(MILLISECOND));
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

/**
 * Starts the philosopher's life routine.
 * Creates a monitor thread for checking death conditions.
 * The routine cycles through eating, sleeping, and thinking states.
 * Exits when philosopher reaches maximum eat count.
 *
 * @param philo Pointer to the philosopher.
 */
void	start_routine(t_philo *philo)
{
	set_long(philo->table->last_meal, &philo->last_m, gettime_b(MILLISECOND));
	pthread_create(&philo->monitor_thread, NULL, (void *)monitor_dinner, philo);
	pthread_detach(philo->monitor_thread);
	while (1)
	{
		eat_routine(philo);
		philo->n_eat++;
		if (philo->n_eat == philo->max_eat)
		{
			sem_post(philo->table->all_eat);
			exit(0);
		}
		write_status(philo, SLEEP, gettime_b(MILLISECOND));
		usleep(philo->time_to_sleep);
		thinking(philo, true);
	}
}
