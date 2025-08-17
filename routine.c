/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 11:33:14 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now(pthread_mutex_t *lock, struct timeval *t)
{
	pthread_mutex_lock(lock);
	gettimeofday(t, NULL);
	t->tv_sec = t->tv_sec * 1000 + t->tv_usec / 1000;
	pthread_mutex_unlock(lock);
	return (t->tv_sec);
}

void	get_time(t_philo *philo, struct timeval *t)
{
	pthread_mutex_lock(&(philo->lock));
	gettimeofday(philo->timer, NULL);
	philo->timer->tv_sec = philo->timer->tv_sec * 1000 + philo->timer->tv_usec
		/ 1000;
	pthread_mutex_unlock(&(philo->lock));
	now(&(philo->lock), t);
}

void	thinking(t_philo *philo)
{
	if (get_bool(&(philo->lock), philo->die))
		return ;
	print_action(&(philo->input->lock), philo, philo->start->tv_sec, THINKING);
	usleep(500);
	while (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		if (get_bool(&(philo->lock), philo->die))
			return ;
	}
}

void	get_fork(t_philo *philo)
{
	if (philo->num_of_phil % 2 == 1)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
	}
	print_action(&(philo->input->lock), philo, philo->start->tv_sec, FORKING);
	print_action(&(philo->input->lock), philo, philo->start->tv_sec, FORKING);
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	pthread_mutex_lock(&(philo->lock_last));
	get_time(philo, &t);
	print_action(&(philo->input->lock), philo, philo->start->tv_sec, EATING);
	usleep((t.tv_sec - philo->timer->tv_sec) / 2);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_eat
		&& !get_bool(&(philo->lock), philo->die))
		now(&(philo->lock), &t);
	now(&(philo->lock), philo->last);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(&(philo->lock_last));
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	if (get_bool(&(philo->lock), philo->die))
		return ;
	print_action(&(philo->input->lock), philo, philo->start->tv_sec, SLEEPING);
	usleep((t.tv_sec - philo->timer->tv_sec) / 2);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_sleep
		&& !get_bool(&(philo->lock), philo->die))
		now(&(philo->lock), &t);
}

void	*routine(void *philos)
{
	t_philo	philo;
	long		i;

	i = 0;
	philo = *(t_philo *)philos;
	while (!get_bool(&(philo.input->lock), &(philo.input->ready)))
		;
	now(&(philo.lock), philo.start);
	now(&(philo.lock), philo.last);
	if (philo.num % 2 == 1)
	{
		thinking(&philo);
	}
	while (!get_bool(&(philo.lock), philo.die))
	{
		eating(&philo);
		if (philo.num_of_meals != 0 && ++i == philo.num_of_meals)
			set_bool(&(philo.lock), philo.full, true);
		if (get_bool(&(philo.lock), philo.die))
			break ;
		sleeping(&philo);
		if (get_bool(&(philo.lock), philo.die))
			break ;
		thinking(&philo);
		if (get_bool(&(philo.lock), philo.die))
			break ;
	}
	return (philos);
}
