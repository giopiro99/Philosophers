/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:20:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/25 12:35:15 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1)parsing
//2)init data
//3)start dinner
//4)free all
int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (ac == 5 || ac == 6)
	{
		if (parsing(table, av) == -1)
			return (free(table), -1);
		else
		{
			if (init_data(table) == -1)
				return (free(table), -1);
			else
			{
				if (start_dinner(table) == -1)
					return (free(table), error_ex("Error to start"), -1);
				free_all(table);
			}
		}
	}
	else
		return (free(table), error_ex("Error input"), -1);
	return (0);
}
