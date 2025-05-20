/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:24:10 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/26 11:43:43 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
