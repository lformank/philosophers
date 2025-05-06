/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/05/04 13:46:04 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	now(struct timeval	*t)
{
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
}

void	get_time(t_philo *philo, struct timeval	*t)
{
	gettimeofday(philo->timer, NULL);
	philo->timer->tv_sec = philo->timer->tv_sec * 1000 + philo->timer->tv_usec / 1000;
	now(t);
}

void	thinking(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	printf("%ld %d is thinking\n", t.tv_sec - philo->start->tv_sec, philo->num);
	while(t.tv_sec - philo->timer->tv_sec < 20 && philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		if (*(philo)->die == 1)
			return ;
	}
}

void	get_fork(t_philo *philo)
{
	struct timeval	t;

	if (philo->num % 2 == 1)
	{
		now(&t);
		pthread_mutex_lock(philo->rfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
		pthread_mutex_lock(philo->lfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
		
	}
	if (philo->num % 2 == 0)
	{
		now(&t);
		pthread_mutex_lock(philo->lfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
		pthread_mutex_lock(philo->rfork);
		printf("%ld %d has taken a fork\n", t.tv_sec - philo->start->tv_sec, philo->num);
	}
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	get_time(philo, &t);
	if (philo->lfork && philo->rfork)
	{
		now(philo->last);
		printf("%ld %d is eating\n", t.tv_sec - philo->start->tv_sec, philo->num);
		while (t.tv_sec - philo->timer->tv_sec <= philo->time_to_eat)
		{
			if (*(philo)->die == 1)
				break ;
			now(&t);
		}
		now(philo->last);
	}
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	if (*(philo)->die == true)
		return ;
	*(philo)->full += 1;
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	printf("%ld %d is sleeping\n", t.tv_sec - philo->start->tv_sec, philo->num);
	while (t.tv_sec - philo->timer->tv_sec <= philo->time_to_sleep)
	{
		if (*(philo)->die == 1)
			return ;
		now(&t);
	}
}

void	*routine(void *philos)
{
	t_philo			philo;
	int	i;

	i = 0;
	philo = *(t_philo *)philos;
	while (*(philo).set == false)
		;
	now(philo.start);
	if (philo.num == philo.num_of_phil)
		sleeping(&philo);
	while (*(philo).die == 0)
	{
		if (i != 0 && i == philo.num_of_meals)
			*(philo).full = true;
		thinking(&philo);
		if (*(philo).die == 1)
			return(philos);
		eating(&philo);
		if (*(philo).die == 1)
			return(philos);
		sleeping(&philo);
		if (*(philo).die == 1)
			return(philos);
		i++;
	}
	return (philos);
}
