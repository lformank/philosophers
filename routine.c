/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/05/11 21:37:36 by lformank         ###   ########.fr       */
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
	print_action(philo->to_write, philo, philo->start->tv_sec, THINKING);
	while (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		if (get_bool(philo->to_write, philo->die))
			return ;
	}
}

void	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_action(philo->to_write, philo, philo->start->tv_sec, FORKING);
	pthread_mutex_lock(philo->rfork);
	print_action(philo->to_write, philo, philo->start->tv_sec, FORKING);	
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	get_time(philo, &t);
	if (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		now(philo->to_write, philo->last);
		print_action(philo->to_write, philo, philo->start->tv_sec, EATING);
		while (t.tv_sec - philo->timer->tv_sec <= philo->time_to_eat)
		{
			if (get_bool(philo->to_write, philo->die))
				break ;
			now(philo->to_write, &t);
		}
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		now(philo->to_write, philo->last);
	}
	if (*(philo)->die == true)
		return ;
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	print_action(philo->to_write, philo, philo->start->tv_sec, SLEEPING);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_sleep
		&& !get_bool(philo->to_write, philo->die))
	{
		if (get_bool(philo->to_write, philo->die))
			return ;
		now(philo->to_write, &t);
	}
}

void	*routine(void *philos)
{
	t_philo			philo;
	int	i;

	i = -1;
	philo = *(t_philo *)philos;
	while (!get_bool(&philo.input->read, &philo.input->ready))
		;
	now(philo.to_write, philo.start);
	if (philo.num == philo.num_of_phil)
		sleeping(&philo);
	while (!get_bool(philo.to_write, philo.die))
	{
		thinking(&philo);
		if (get_bool(philo.to_write, philo.die))
			return (philos);
		eating(&philo);
		if (get_bool(philo.to_write, philo.die))
			return (philos);
		sleeping(&philo);
		if (get_bool(philo.to_write, philo.die))
			return (philos);
		if (++i != 0 && i == philo.num_of_meals - 1)
			set_bool(&philo.input->read, philo.full, true);
	}
	return (philos);
}
