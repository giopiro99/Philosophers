/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:31:54 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/03/26 18:21:28 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_long(sem_t *sem, long *dest)
{
	long	ret;

	sem_wait(sem);
	ret = (*dest);
	sem_post(sem);
	return (ret);
}

void	set_long(sem_t *sem, long *dest, long value)
{
	sem_wait(sem);
	(*dest) = value;
	sem_post(sem);
}
