/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:45:00 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:37:46 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Checks if the character is a whitespace character.
 *
 * @param c The character to check.
 * @return 1 if c is a whitespace (space, tab, newline, etc.), 0 otherwise.
 */
int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/**
 * Converts a string to a long integer.
 * Returns -1 and prints an error if the string contains invalid characters,
 * a negative sign, or a number larger than INT_MAX.
 *
 * @param s The input string.
 * @return The converted long integer, or -1 on error.
 */
long	atol(const char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		return (error_ex("Negative n detected\n"), -1);
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	if (res > INT_MAX)
		return (error_ex("too hight number\n"), -1);
	return (res);
}

/**
 * Parses command line arguments to initialize the simulation parameters.
 *
 * @param table Pointer to the table struct to fill.
 * @param av Argument vector containing the input strings.
 * @return 0 on success, -1 on invalid input.
 */
long	parsing_bonus(t_table *table, char **av)
{
	table->philo_nbr = atol(av[1]);
	table->time_to_die = atol(av[2]) * 1e3;
	table->time_to_eat = atol(av[3]) * 1e3;
	table->time_to_sleep = atol(av[4]) * 1e3;
	if (table->philo_nbr <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (error_ex("invalid input\n"),-1);
	if (av[5])
	{
		table->max_eat = atol(av[5]);
		if (table->max_eat <= 0)
			return (error_ex("wrong max eat number\n"), -1);
		else
			return (0);
	}
	else
		table->max_eat = -1;
	return (0);
}
