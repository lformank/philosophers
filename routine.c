/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/05/09 17:23:34 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	now(pthread_mutex_t *lock, struct timeval *t)
{
	pthread_mutex_lock(lock);
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
	pthread_mutex_unlock(lock);
	return (t->tv_sec);
}

void	get_time(t_philo *philo, struct timeval	*t)
{
	pthread_mutex_lock(philo->to_write);
	gettimeofday(philo->timer, NULL);
	philo->timer->tv_sec = philo->timer->tv_sec * 1000 + philo->timer->tv_usec / 1000;
	pthread_mutex_unlock(philo->to_write);
	now(philo->to_write, t);
}

void	thinking(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	printf("%ld %d is thinking\n", t.tv_sec - philo->start->tv_sec, philo->num);
	while(philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		if (*(philo)->die == true)
			return ;
	}
}

void	get_fork(t_philo *philo)
{
	struct timeval	t;

		now(philo->to_write, &t);
		pthread_mutex_lock(philo->lfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
		now(philo->to_write, &t);
		pthread_mutex_lock(philo->rfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	get_time(philo, &t);
	if (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		now(philo->to_write, philo->last);
		printf("%ld %d is eating\n", t.tv_sec - philo->start->tv_sec, philo->num);
		while (t.tv_sec - philo->timer->tv_sec <= philo->time_to_eat)
		{
			if (*(philo)->die == true)
				break ;
			now(philo->to_write, &t);
		}
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		now(philo->to_write, philo->last);
	}
	if (*(philo)->die == true)
		return ;
	set_long(philo->to_write, philo->full, *(philo)->full + 1);
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	printf("%ld %d is sleeping\n", t.tv_sec - philo->start->tv_sec, philo->num);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_sleep)
	{
		if (*(philo)->die == 1)
			return ;
		now(philo->to_write, &t);
	}
}

void	*routine(void *philos)
{
	t_philo			philo;
	int	i;

	i = 0;
	philo = *(t_philo *)philos;
	while (!get_bool(&philo.input->read, &philo.input->ready))
		;
	now(philo.to_write, philo.start);
	while (!get_bool(philo.to_write, philo.die) /*&& !get_bool(philo.to_write, philo.full)*/)
	{
		i++;
		thinking(&philo);
		if (*(philo).die == 1)
			return(philos);
		eating(&philo);
		if (*(philo).die == 1)
			return(philos);
		sleeping(&philo);
		if (*(philo).die == 1)
			return(philos);
		// if (i != 0 && i == philo.num_of_meals)
	}
	return (philos);
}
