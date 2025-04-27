/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/04/26 13:54:35 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(t_philo *philo, struct timeval	*t)
{
	gettimeofday(philo->timer, NULL);
	philo->timer->tv_sec = philo->timer->tv_sec * 1000 + philo->timer->tv_usec / 1000;
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
}

void	now(struct timeval	*t)
{
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
}

void	thinking(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	while (t.tv_sec - philo->timer->tv_sec < 100)
		now(&t);
	printf("%d: start: %ld ms, thinking: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->timer->tv_sec);
}

void	get_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
		philo->ready = true;
	}
	if (philo->num % 2 == 1)
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
		philo->ready = true;
	}
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	get_time(philo, &t);
	now(&philo->last);
	if (philo->lfork && philo->rfork)
		while (t.tv_sec - philo->timer->tv_sec < philo->time_to_eat)
			now(&t);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	philo->ready = false;
	printf("%d: start: %ld ms, eating: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->timer->tv_sec);
	}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_sleep)
		now(&t);
	printf("%d: start: %ld ms, sleeping: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->timer->tv_sec);
}

void	*routine(void *philos)
{
	t_philo			philo;
	int	i;

	i = 0;
	philo = *(t_philo *)philos;
	now(philo.start);
	while (*(philo).die == 0)
	{
		if (philo.num_of_meals != 0 && i == philo.num_of_meals)
			*(philo).full = true;
		thinking(&philo);
		eating(&philo);
		sleeping(&philo);
		i++;
		// if (i == 3)
		// 	*(philo).die += 1;
	}
	return (philos);
}
