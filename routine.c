/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/04/12 16:19:19 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	struct timeval	t;
	long int		time;
	long int		philo_time;


	gettimeofday(philo->ms, NULL);
	philo_time = philo->ms->tv_sec * 1000 + philo->ms->tv_usec / 1000;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	while (time - philo_time < 1)
	{
		usleep(100);
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000 + t.tv_usec / 1000;
		printf("%d: start: %ld ms, thinking: %ld ms\n", philo->num, time - philo->start->tv_sec, time - philo_time);
	}
}

void	get_fork(t_philo *philo)
{
	pthread_mutex_init(&philo->lock, NULL);
	pthread_mutex_lock(&philo->lock);
	if (!*(philo)->lfork)
	{
		if (philo->num == philo->num_of_phil)
		{
			*(philo)->lfork = &philo->table->forks[0];
			philo->table->forks[0] = false;
		}
		else
		{
			*(philo)->lfork = &philo->table->forks[philo->num];
			philo->table->forks[philo->num] = false;
		}
	}
	if (!*(philo)->rfork)
	{
		*(philo)->rfork = &philo->table->forks[philo->num - 1];
		philo->table->forks[philo->num - 1] = false;
	}
}

void	eating(t_philo *philo)
{
	struct timeval	t;
	long int		time;
	long int		philo_time;

	get_fork(philo);
	gettimeofday(philo->ms, NULL);
	philo_time = philo->ms->tv_sec * 1000 + philo->ms->tv_usec / 1000;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	if (philo->lfork && philo->rfork)
	{
		while (time - philo_time < philo->time_to_eat)
		{
			usleep(100);
			gettimeofday(&t, NULL);
			time = t.tv_sec * 1000 + t.tv_usec / 1000;
			printf("%d: start: %ld ms, eating: %ld ms\n", philo->num, time - philo->start->tv_sec, time - philo_time);
		}
		if (philo->num == philo->num_of_phil)
			philo->table->forks[0] = true;
		else
			philo->table->forks[philo->num] = true;
		philo->table->forks[philo->num - 1] = true;
	}
	pthread_mutex_unlock(&philo->lock);
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;
	long int		time;
	long int		philo_time;


	gettimeofday(philo->ms, NULL);
	philo_time = philo->ms->tv_sec * 1000 + philo->ms->tv_usec / 1000;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	while (time - philo_time < philo->time_to_sleep)
	{
		usleep(500);
		gettimeofday(&t, NULL);
		time = t.tv_sec * 1000 + t.tv_usec / 1000;
		printf("%d: start: %ld ms, sleeping: %ld ms\n", philo->num, time - philo->start->tv_sec, time - philo_time);
	}
}

void	even_routine(t_philo *philo)
{
	int	i;

	i = 0;
	while (*(philo)->die == 0)
	{
		if (philo->num_of_meals && i == philo->num_of_meals)
			*(philo)->full = 1;
		if (philo->num % 2 == 0)
		{
			thinking(philo);
			eating(philo);
			sleeping(philo);
		}
		if (philo->num % 2 == 1)
		{
			sleeping(philo);
			thinking(philo);
			eating(philo);
		}
		i++;
		if (i == 3)
			*(philo)->die += 1;
	}
}

// void	odd_routine(t_philo *philo)
// {
// 	thinking ()
// }

void	*routine(void *philos)
{
	t_philo			philo;

	philo = *(t_philo *)philos;
	gettimeofday(philo.start, NULL);
	philo.start->tv_sec = philo.start->tv_sec * 1000 + philo.start->tv_usec / 1000;
	if ((philo.num_of_phil % 2) == 0)
		even_routine(philos);
	// else if (philo.num_of_phil % 2 == 1)
		//odd_routine(); // TODO
	return (philos);
}
