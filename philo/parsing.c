/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:28:10 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:28:21 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if the character is a whitespace character (space, tab, newline, etc.)
int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

// Checks if the character is a digit ('0' to '9')
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// Converts string to a positive long integer; returns -1 on error or negative input
long	ft_atol(const char *str)
{
	long		res;
	int			i;
	const char	*number;

	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (error_ex("negative number detected\n"), -1);
	if (!ft_isdigit(str[i]))
		return (-1);
	number = str;
	while (number[i] >= '0' && number[i] <= '9')
	{
		res = (res * 10) + (number[i] - 48);
		i++;
	}
	if (res > INT_MAX || res <= 0)
		return (-1);
	return (res);
}
// Parses command line arguments into the t_table structure
// av[1] = number_of_philosophers
// av[2] = time_to_die (ms)
// av[3] = time_to_eat (ms)
// av[4] = time_to_sleep (ms)
// av[5] = max_meals (optional)
// Times are converted from milliseconds to microseconds (*1000) for usleep compatibility
long	parsing(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
	{
		table->max_eat = ft_atol(av[5]);
		if (table->max_eat < 0)
			return (error_ex("max eat invalid\n"), -1);
		else if (table->max_eat == 0)
			return (-1);
	}
	else
		table->max_eat = -1;
	if (table->philo_nbr <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (error_ex("Invalid input\n"), -1);
	return (0);
}
