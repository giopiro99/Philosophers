/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:24:10 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:37:10 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Entry point of the program.
 * Parses input arguments, initializes data, starts the dinner simulation,
 * and then frees all allocated resources.
 *
 * @param ac Argument count.
 * @param av Argument vector (array of strings).
 * @return 0 on success, -1 on failure.
 */
int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (ac == 5 || ac == 6)
	{
		if (parsing_bonus(table, av) == -1)
			return (free(table), -1);
		else
		{
			if (init_data_bonus(table) == -1)
				return (free(table), -1);
			start_dinner_bonus(table);
			free_all(table);
		}
	}
	else
		return (free(table), error_ex("Wrong input\n"), -1);
}
