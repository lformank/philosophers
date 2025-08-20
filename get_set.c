/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:51:58 by lformank          #+#    #+#             */
/*   Updated: 2025/08/20 12:49:32 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(pthread_mutex_t *lock, bool *variable)
{
	bool	value;

	pthread_mutex_lock(lock);
	value = *variable;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_bool(pthread_mutex_t *lock, bool *variable, bool value)
{
	pthread_mutex_lock(lock);
	*variable = value;
	pthread_mutex_unlock(lock);
}

long	get_long(pthread_mutex_t *lock, long *variable)
{
	long	value;

	pthread_mutex_lock(lock);
	value = *variable;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_long(pthread_mutex_t *lock, long *variable, long value)
{
	pthread_mutex_lock(lock);
	*variable = value;
	pthread_mutex_unlock(lock);
}
