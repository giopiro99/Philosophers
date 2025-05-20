/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:08:55 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/26 18:26:51 by gpirozzi         ###   ########.fr       */
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
//code more readible
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
//to write status
typedef enum s_write
{
	THINK,
	SLEEP,
	EAT,
	DIE,
	TAKE_FIRST,
	TAKE_SECOND,
}	t_write;
//for gettime
typedef enum s_time
{
	MILLISECOND,
}	t_time;
//fork struct
typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;
//Philo struct
typedef struct s_philo
{
	bool		full;
	long		last_meal_time;
	int			philo_id;
	int			meal_counter;
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	t_mtx		philo_mutex;
}	t_philo;
//The table
typedef struct s_table
{
	t_philo		*philos;
	t_fork		*forks;
	t_mtx		write_mutex;
	t_mtx		table_mtx;
	pthread_t	monitor;
	long		time_to_eat;
	long		start_simulation;
	long		time_to_sleep;
	long		time_to_die;
	int			philo_nbr;
	long		max_eat;
	bool		end_simulation;//1 philo die || all philo full
	long		threads_running;//all trheads are ready to start
	bool		threads_ready;
}	t_table;
//functions
long	parsing(t_table *table, char **av);
long	init_data(t_table *table);
long	start_dinner(t_table *table);
void	error_ex(const char *error);
void	free_all(t_table *table);
void	to_write_status(t_philo *philo, t_write status, long time);
void	*lone_philo(t_philo *philo);
void	*monitor_dinner(t_table *table);
long	start_dinner(t_table *table);
bool	philo_die(t_philo *philo);
//safe read
void	increase_long(t_mtx *mutex, long *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *dest);
bool	simulation_finish(t_table *table);
long	get_long(t_mtx *mutex, long *dest);
//syncro
void	wait_threads(t_table *table);
long	gettime(t_time format);
void	thinking(t_philo *philo, bool flag);
void	desync(t_philo *philo);
bool	all_threads_running(t_mtx *mutex, long *thread, long philo_nbr);

#endif
