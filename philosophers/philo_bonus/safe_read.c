/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:31:54 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 17:36:51 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * Thread-safe read of a long integer protected by a semaphore.
 *
 * @param sem Semaphore used to protect access.
 * @param dest Pointer to the long integer to read.
 * @return The value read from *dest.
 */
long	get_long(sem_t *sem, long *dest)
{
	long	ret;

	sem_wait(sem);
	ret = (*dest);
	sem_post(sem);
	return (ret);
}

/**
 * Thread-safe write of a long integer protected by a semaphore.
 *
 * @param sem Semaphore used to protect access.
 * @param dest Pointer to the long integer to write.
 * @param value Value to write into *dest.
 */
void	set_long(sem_t *sem, long *dest, long value)
{
	sem_wait(sem);
	(*dest) = value;
	sem_post(sem);
}
