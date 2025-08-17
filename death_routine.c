/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 10:55:41 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_philo *philo)
{
	long	i;

	i = -1;
	while (++i < philo->num_of_phil)
		set_bool(&(philo->lock), philo->die, true);
}

int	check_death(t_philo *philo, pthread_mutex_t *lock)
{
	struct timeval	t;

	if (now(lock, &t) - get_long(lock, &(philo->last->tv_sec))
		>= get_long(lock, &(philo->time_to_die)))
	{
		set_bool(lock, philo->die, true);
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	long	i;
	long	count;

	i = -1;
	count = 0;
	while (++i < philo->num_of_phil)
	{
		if (get_bool(&(philo->lock), philo->full) == true)
			count++;
		if (count == philo->num_of_phil)
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
		if (check_death(&(input->philos[i]), &(input->philos[i].lock)) == 1)
		{
			print_action(&(input->lock), &input->philos[i],
				input->philos[i].start->tv_sec, DIE);
			kill_philos(&(input->philos[i]));
			return ;
		}
		if (check_meals(&(input->philos[i])) == 1)
			kill_philos(&(input->philos[i]));
		if (i == input->num_of_phil - 1)
			i = -1;
		i++;
	}
	free_input(input);
}
