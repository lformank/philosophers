/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/08/16 15:59:46 by lformank         ###   ########.fr       */
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

void	get_time(t_philo *philo, struct timeval *t)
{
	pthread_mutex_lock(&(philo)->check);
	gettimeofday(philo->timer, NULL);
	philo->timer->tv_sec = philo->timer->tv_sec * 1000 + philo->timer->tv_usec
		/ 1000;
	pthread_mutex_unlock(&(philo)->check);
	now(&(philo)->check, t);
}

void	thinking(t_philo *philo)
{
	if (get_bool(&philo->input->death->die_lock, philo->die))
		return ;
	print_action(&philo->input->prt, philo, philo->start->tv_sec, THINKING);
	usleep(500);
	while (philo->lfork->__data.__lock && philo->rfork->__data.__lock)
	{
		if (get_bool(&philo->input->death->die_lock, philo->die))
			return ;
	}
}

void	get_fork(t_philo *philo)
{
	if (philo->num_of_phil % 2 == 1)
	{
		printf("DEBUG: Philo %d TRYING to take LEFT fork\n", philo->num);
		pthread_mutex_lock(philo->lfork);
		printf("DEBUG: Philo %d has TAKEN LEFT fork\n", philo->num);
		printf("DEBUG: Philo %d TRYING to take RIGHT fork\n", philo->num);
		pthread_mutex_lock(philo->rfork);
		printf("DEBUG: Philo %d has TAKEN RIGHT fork\n", philo->num);
	}
	else
	{
		printf("DEBUG: Philo %d TRYING to take RIGHT fork\n", philo->num);
		pthread_mutex_lock(philo->rfork);
		printf("DEBUG: Philo %d has TAKEN RIGHT fork\n", philo->num);
		printf("DEBUG: Philo %d TRYING to take LEFT fork\n", philo->num);
		pthread_mutex_lock(philo->lfork);
		printf("DEBUG: Philo %d has TAKEN LEFT fork\n", philo->num);
	}
	print_action(&(philo)->input->prt, philo, philo->start->tv_sec, FORKING);
	print_action(&(philo)->input->prt, philo, philo->start->tv_sec, FORKING);
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	get_fork(philo);
	now(&(philo)->check, philo->last);
	get_time(philo, &t);
	print_action(&(philo)->input->prt, philo, philo->start->tv_sec, EATING);
	usleep((t.tv_sec - philo->timer->tv_sec) / 2);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_eat
		&& !get_bool(&philo->input->death->die_lock, philo->die))
		now(&(philo)->check, &t);
	pthread_mutex_unlock(philo->lfork);
    printf("DEBUG: Philo %d has RELEASED LEFT fork\n", philo->num);
	pthread_mutex_unlock(philo->rfork);
    printf("DEBUG: Philo %d has RELEASED RIGHT fork\n", philo->num);
	now(&(philo)->check, philo->last);
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	get_time(philo, &t);
	if (get_bool(&philo->input->death->die_lock, philo->die))
		return ;
	print_action(&(philo)->input->prt, philo, philo->start->tv_sec, SLEEPING);
	usleep((t.tv_sec - philo->timer->tv_sec) / 2);
	while (t.tv_sec - philo->timer->tv_sec < philo->time_to_sleep
		&& !get_bool(&philo->input->death->die_lock, philo->die))
		now(&(philo)->check, &t);
}

void	*routine(void *philos)
{
	t_philo	philo;
	int		i;

	i = 0;
	philo = *(t_philo *)philos;
	while (!get_bool(&philo.input->prt, &philo.input->ready))
		;
	now(&(philo).check, philo.start);
	now(&(philo).check, philo.last);
	if (philo.num % 2 == 1)
		thinking(&philo);
	while (!get_bool(&(philo.input->death->die_lock), philo.die))
	{
		eating(&philo);
		if (philo.num_of_meals != 0 && ++i == philo.num_of_meals)
			set_bool(&(philo.input->death->full_lock), philo.full, true);
		if (get_bool(&(philo.input->death->die_lock), philo.die))
			break ;
		sleeping(&philo);
		if (get_bool(&(philo.input->death->die_lock), philo.die))
			break ;
		thinking(&philo);
		if (get_bool(&(philo.input->death->die_lock), philo.die))
			break ;
	}
	return (philos);
}
