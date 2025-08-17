/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 15:49:10 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_input *input)
{
	long	i;

	i = -1;
	while (++i < input->num_of_phil)
		set_bool(&(input->philos[i].lock), input->philos[i].die, true);
}

int	check_death(t_philo *philo)
{
	struct timeval	t;
	long			since_last;

	pthread_mutex_lock(&(philo->lock));
	gettimeofday(&t, NULL);
	t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
	since_last = t.tv_sec - philo->last->tv_sec;
	if (since_last >= philo->time_to_die)
	{
		pthread_mutex_unlock(&(philo->lock));
		return (1);
	}
	pthread_mutex_unlock(&(philo->lock));
	return (0);
}

int	check_meals(t_input *input)
{
	long	i;
	long	count;

	i = -1;
	count = 0;
	while (++i < input->num_of_phil)
	{
		if (get_bool(&(input->philos[i].lock), input->philos[i].full) == true)
		{
			count++;
		}
		if (count == input->num_of_phil)
			return (1);
	}
	return (0);
}

void	droutine(t_input *input)
{
	long		i;

	i = 0;
	while (!get_bool(&(input->philos[i].lock), input->philos[i].die))
	{
		if (check_death(&(input->philos[i])) == 1)
		{
			print_action(&(input->lock), &input->philos[i], input->philos[i].start->tv_sec, DIE);
			kill_philos(input);
			return ;
		}
		if (check_meals(input) == 1)
			kill_philos(input);
		if (i == input->num_of_phil - 1)
			i = 0;
		i++;
	}
	free_input(input);
}
