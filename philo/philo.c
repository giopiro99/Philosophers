/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:20:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:27:20 by gpirozzi         ###   ########.fr       */
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
	if (!table)
		return (error_ex("Memory allocation failed\n"), -1);
	// Check for correct number of arguments (4 or 5 user params + program name)
	if (ac == 5 || ac == 6)
	{
		if (parsing(table, av) == -1)
			return (free(table), -1);
		if (init_data(table) == -1)
			return (free(table), -1);
		if (start_dinner(table) == -1)
			return (free(table), error_ex("Error starting simulation\n"), -1);
		free_all(table);
	}
	else
	{
		free(table);
		return (error_ex("Invalid number of arguments\n"), -1);
	}
	return (0);
}

