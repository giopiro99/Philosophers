/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:08:55 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:01:07 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <time.h>

/*
 * Type alias for pthread mutex for code readability
 */
typedef pthread_mutex_t	t_mtx;

/*
 * Forward declaration of table struct for references in other structs
 */
typedef struct s_table	t_table;

/*
 * Enum for philosopher statuses, used in status writing function
 */
typedef enum s_write
{
	THINK,
	SLEEP,
	EAT,
	DIE,
	TAKE_FIRST,
	TAKE_SECOND,
}	t_write;

/*
 * Enum for time units, currently only millisecond supported
 */
typedef enum s_time
{
	MILLISECOND,
}	t_time;

/*
 * Fork structure with an ID and associated mutex
 */
typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

/*
 * Philosopher structure representing each philosopher thread
 */
typedef struct s_philo
{
	bool		full;             // Flag: philosopher ate max meals
	long		last_meal_time;   // Timestamp of last meal
	int			philo_id;         // Philosopher ID
	int			meal_counter;     // Number of meals eaten
	pthread_t	thread_id;        // Thread ID
	t_fork		*first_fork;     // Pointer to first fork (mutex)
	t_fork		*second_fork;    // Pointer to second fork (mutex)
	t_table		*table;           // Pointer to shared table data
	t_mtx		philo_mutex;      // Mutex protecting philosopher's data
}	t_philo;

/*
 * Table structure representing shared simulation data and resources
 */
typedef struct s_table
{
	t_philo		*philos;          // Array of philosophers
	t_fork		*forks;           // Array of forks
	t_mtx		write_mutex;      // Mutex for synchronized output
	t_mtx		table_mtx;        // General mutex for table access
	pthread_t	monitor;          // Thread for monitoring simulation
	long		time_to_eat;      // Time each philosopher spends eating
	long		start_simulation; // Timestamp simulation started
	long		time_to_sleep;    // Time each philosopher spends sleeping
	long		time_to_die;      // Max time before philosopher dies
	int			philo_nbr;        // Number of philosophers
	long		max_eat;          // Maximum meals each philosopher should eat
	bool		end_simulation;   // Flag: 1 if one philosopher died or all full
	long		threads_running;  // Number of threads ready to start
	bool		threads_ready;    // Flag indicating if threads are ready
}	t_table;

/* Function prototypes */

/* Parsing and initialization */
long	parsing(t_table *table, char **av);
long	init_data(t_table *table);

/* Simulation control */
long	start_dinner(t_table *table);
void	error_ex(const char *error);
void	free_all(t_table *table);

/* Philosopher status and thread routines */
void	to_write_status(t_philo *philo, t_write status, long time);
void	*lone_philo(t_philo *philo);
void	*monitor_dinner(t_table *table);
bool	philo_die(t_philo *philo);

/* Thread-safe variable accessors */
void	increase_long(t_mtx *mutex, long *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *dest);
bool	simulation_finish(t_table *table);
long	get_long(t_mtx *mutex, long *dest);

/* Thread synchronization and utility */
void	wait_threads(t_table *table);
long	gettime(t_time format);
void	thinking(t_philo *philo, bool flag);
void	desync(t_philo *philo);
bool	all_threads_running(t_mtx *mutex, long *thread, long philo_nbr);

#endif

