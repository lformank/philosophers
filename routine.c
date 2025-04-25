/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/04/25 16:12:03 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	get_time(t_philo *philo, struct timeval	*t)
{
	gettimeofday(philo->ms, NULL);
	philo->ms->tv_sec = philo->ms->tv_sec * 1000 + philo->ms->tv_usec / 1000;
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
}

void	thinking(t_philo *philo)
{
	struct timeval	t;


	get_time(philo, &t);
	while (t.tv_sec - philo->ms->tv_sec < 1)
	{
		gettimeofday(&t, NULL);
		t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
	}
	gettimeofday(&t, NULL);
	t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
	printf("%d: start: %ld ms, thinking: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->ms->tv_sec);
}

void	get_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
		printf("%d lfork: %p rfork: %p\n", philo->num, philo->lfork, philo->rfork);
	}
	if (philo->num % 2 == 1)
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
		printf("%d lfork: %p rfork: %p\n", philo->num, philo->lfork, philo->rfork);
	}
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	pthread_mutex_init(philo->lfork, NULL);
	pthread_mutex_init(philo->rfork, NULL);
	while (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
		;
	get_fork(philo);
	get_time(philo, &t);
	if (philo->lfork && philo->rfork)
	{
		while (t.tv_sec - philo->ms->tv_sec < philo->time_to_eat)
		{
			usleep(100);
			gettimeofday(&t, NULL);
			t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
		}
	}
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_destroy(philo->lfork);
	pthread_mutex_destroy(philo->rfork);
	printf("%d: start: %ld ms, eating: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->ms->tv_sec);
	}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	while (t.tv_sec - philo->ms->tv_sec < philo->time_to_sleep)
	{
		usleep(500);
		gettimeofday(&t, NULL);
		t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
	}
	printf("%d: start: %ld ms, sleeping: %ld ms\n", philo->num, t.tv_sec - philo->start->tv_sec, t.tv_sec - philo->ms->tv_sec);
}

void	*routine(void *philos)
{
	t_philo			philo;
	int	i;

	i = 0;
	philo = *(t_philo *)philos;
	gettimeofday(philo.start, NULL);
	philo.start->tv_sec = philo.start->tv_sec * 1000 + philo.start->tv_usec / 1000;
	while (*(philo).die == 0)
	{
		if (philo.num_of_meals != 0 && i == philo.num_of_meals)
			*(philo).full = true;
		thinking(&philo);
		eating(&philo);
		sleeping(&philo);
		i++;
		if (i == 3)
			*(philo).die += 1;
	}
	return (philos);
}
