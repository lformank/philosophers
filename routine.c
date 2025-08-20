/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/08/20 12:49:13 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *phil)
{
	if (get_bool(&(phil->lock), &(phil->die)))
		return ;
	print_action(&(phil->input->lock), phil, *(phil->input->start), THINKING);
	usleep(5000);
}

void	get_fork(t_philo *philo)
{
	if (philo->num % 2 == 1 && !get_bool(&(philo->lock), &(philo->die)))
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->lfork);
	}
	else if (!get_bool(&(philo->lock), &(philo->die)))
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
	}
	else
		return ;
	print_action(&(philo->input->lock), philo, *(philo->input->start), FORKING);
	print_action(&(philo->input->lock), philo, *(philo->input->start), FORKING);
}

void	eating(t_philo *philo)
{
	long	since_eat;

	get_fork(philo);
	set_long(&(philo->lock), &(philo->last->tv_sec), now());
	since_eat = now();
	print_action(&(philo->input->lock), philo, *(philo->input->start), EATING);
	usleep((philo->time_to_eat / 2) * 1000);
	while (now() - since_eat < philo->time_to_eat
		&& !get_bool(&(philo->lock), &(philo->die)))
		usleep(100);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	sleeping(t_philo *philo)
{
	long	since_sleep;

	since_sleep = now();
	if (get_bool(&(philo->lock), &(philo->die)))
		return ;
	print_action(&(philo->input->lock), philo, *(philo->input->start), SLEEP);
	while (now() - since_sleep < philo->time_to_sleep
		&& !get_bool(&(philo->lock), &(philo->die)))
		usleep(100);
}

void	*routine(void *philos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)philos;
	while (!get_bool(&(philo->input->lock), &(philo->input->ready)))
		usleep(500);
	set_long(&(philo->lock), &(philo->last->tv_sec), now());
	if (philo->num % 2 == 1)
		thinking(philo);
	while (!get_bool(&(philo->lock), &(philo->die)))
	{
		eating(philo);
		if (++i == philo->num_of_meals && philo->num_of_meals != 0)
			set_bool(&(philo->lock), &(philo->full), true);
		if (get_bool(&(philo->lock), &(philo->die)))
			break ;
		sleeping(philo);
		if (get_bool(&(philo->lock), &(philo->die)))
			break ;
		thinking(philo);
		if (get_bool(&(philo->lock), &(philo->die)))
			break ;
	}
	return (philos);
}
