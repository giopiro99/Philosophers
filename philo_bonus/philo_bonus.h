/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:26:46 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/27 11:10:33 by gpirozzi         ###   ########.fr       */
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

typedef struct s_table	t_table;
//philo struct
typedef struct s_philo_b
{
	int			philo_id;
	int			philo_nbr;
	long		eating_flag;
	long		n_eat;
	long		last_m;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		max_eat;
	t_table		*table;
	pthread_t	monitor_thread;
}				t_philo;
//the table
typedef struct s_table
{
	int			philo_nbr;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		max_eat;
	long		start_simulation;
	pid_t		monitor_pid;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*to_write;
	sem_t		*end_simulation;
	sem_t		*last_meal;
	sem_t		*death;
	sem_t		*all_eat;
	t_philo		*philos;
}	t_table;
//for write the philo status
typedef enum s_status
{
	THINK,
	SLEEP,
	EAT,
	DIE,
	TAKE_FIRST,
	TAKE_SECOND,
}	t_status;
//for get time
typedef enum s_time
{
	MILLISECOND,
}	t_time;
//for errors
void	error_ex(const char *error);
//parsing the input and init data
long	parsing_bonus(t_table *table, char **av);
long	init_data_bonus(t_table *table);
//the dinner
long	start_dinner_bonus(t_table *table);
void	start_routine(t_philo *philo);
void	eat_routine(t_philo *philo);
void	thinking(t_philo *philo, bool flag);
long	gettime_b(t_time format);
void	*monitor_dinner(void *arg);
void	free_all(t_table *table);
void	desync(t_philo *philo);
//safe read and write
long	get_long(sem_t *sem, long *dest);
void	set_long(sem_t *sem, long *dest, long value);
void	write_status(t_philo *philo, t_status status, long time);


#endif
