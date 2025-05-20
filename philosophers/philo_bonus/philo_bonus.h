/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:26:46 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:35:24 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

/**
 * Main table struct holding simulation parameters and synchronization primitives.
 */
typedef struct s_table	t_table;

/**
 * Philosopher struct representing an individual philosopher in the simulation.
 */
typedef struct s_philo_b
{
	int			philo_id;        /**< Unique philosopher identifier */
	int			philo_nbr;       /**< Total number of philosophers */
	long		eating_flag;     /**< Flag indicating eating state */
	long		n_eat;           /**< Number of times philosopher has eaten */
	long		last_m;          /**< Timestamp of last meal */
	long		time_to_eat;     /**< Time allowed to eat (in microseconds) */
	long		time_to_die;     /**< Time before philosopher dies without eating */
	long		time_to_sleep;   /**< Time allowed to sleep */
	long		max_eat;         /**< Max times philosopher must eat */
	t_table		*table;          /**< Pointer back to the table */
	pthread_t	monitor_thread;  /**< Thread monitoring this philosopher */
}				t_philo;

/**
 * Table struct that manages overall simulation parameters, semaphores,
 * and process IDs.
 */
typedef struct s_table
{
	int			philo_nbr;         /**< Number of philosophers */
	long		time_to_eat;       /**< Time to eat */
	long		time_to_die;       /**< Time to die */
	long		time_to_sleep;     /**< Time to sleep */
	long		max_eat;           /**< Maximum meals */
	long		start_simulation;  /**< Simulation start time */
	pid_t		monitor_pid;       /**< Monitor process ID */
	pid_t		*pids;             /**< Array of philosopher process IDs */
	sem_t		*forks;            /**< Semaphore for forks */
	sem_t		*to_write;         /**< Semaphore to synchronize writes */
	sem_t		*end_simulation;   /**< Semaphore signaling simulation end */
	sem_t		*last_meal;        /**< Semaphore protecting last meal time */
	sem_t		*death;            /**< Semaphore signaling death event */
	sem_t		*all_eat;          /**< Semaphore signaling all philosophers ate */
	t_philo		*philos;           /**< Array of philosophers */
}	t_table;

/**
 * Enumeration representing philosopher status for logging.
 */
typedef enum s_status
{
	THINK,      /**< Philosopher is thinking */
	SLEEP,      /**< Philosopher is sleeping */
	EAT,        /**< Philosopher is eating */
	DIE,        /**< Philosopher died */
	TAKE_FIRST, /**< Philosopher took first fork */
	TAKE_SECOND /**< Philosopher took second fork */
}	t_status;

/**
 * Enumeration representing time formats.
 */
typedef enum s_time
{
	MILLISECOND /**< Time format in milliseconds */
}	t_time;

/**
 * Prints an error message to standard output.
 *
 * @param error Error message string.
 */
void	error_ex(const char *error);

/**
 * Parses input arguments and initializes simulation data.
 *
 * @param table Pointer to simulation table.
 * @param av Argument vector from main.
 * @return 0 on success, -1 on failure.
 */
long	parsing_bonus(t_table *table, char **av);

/**
 * Initializes all required data structures and synchronization primitives.
 *
 * @param table Pointer to simulation table.
 * @return 0 on success, -1 on failure.
 */
long	init_data_bonus(t_table *table);

/**
 * Starts the philosopher dinner simulation.
 *
 * @param table Pointer to simulation table.
 * @return 0 on success, -1 on failure.
 */
long	start_dinner_bonus(t_table *table);

/**
 * Routine executed by each philosopher process.
 *
 * @param philo Pointer to philosopher struct.
 */
void	start_routine(t_philo *philo);

/**
 * Performs eating routine for a philosopher.
 *
 * @param philo Pointer to philosopher struct.
 */
void	eat_routine(t_philo *philo);

/**
 * Makes philosopher think with optional logging.
 *
 * @param philo Pointer to philosopher struct.
 * @param flag If true, logs thinking status.
 */
void	thinking(t_philo *philo, bool flag);

/**
 * Returns the current time in specified format.
 *
 * @param format Time format enum.
 * @return Current time in milliseconds.
 */
long	gettime_b(t_time format);

/**
 * Monitor thread function to watch for simulation events.
 *
 * @param arg Pointer to table struct.
 * @return NULL
 */
void	*monitor_dinner(void *arg);

/**
 * Frees all allocated resources.
 *
 * @param table Pointer to simulation table.
 */
void	free_all(t_table *table);

/**
 * Introduces desynchronization delay for philosophers.
 *
 * @param philo Pointer to philosopher struct.
 */
void	desync(t_philo *philo);

/**
 * Safely reads a long value protected by a semaphore.
 *
 * @param sem Semaphore protecting the value.
 * @param dest Pointer to the long value.
 * @return The value read.
 */
long	get_long(sem_t *sem, long *dest);

/**
 * Safely sets a long value protected by a semaphore.
 *
 * @param sem Semaphore protecting the value.
 * @param dest Pointer to the long value.
 * @param value Value to set.
 */
void	set_long(sem_t *sem, long *dest, long value);

/**
 * Writes philosopher status in a thread-safe manner.
 *
 * @param philo Pointer to philosopher struct.
 * @param status Status to write.
 * @param time Current timestamp.
 */
void	write_status(t_philo *philo, t_status status, long time);

#endif

