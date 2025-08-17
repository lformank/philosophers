/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 14:52:39 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_input *input)
{
	long	i;

	i = -1;
	while (++i < input->num_of_phil)
		set_bool(&(input->lock), input->philos[i].die, true);
}

int	check_death(t_philo *philo, pthread_mutex_t *lock)
{
	if (now() - get_long(&(philo->lock_last), &(philo->last->tv_sec))
		>= get_long(lock, &(philo->time_to_die)))
	{
		set_bool(lock, philo->die, true);
		return (1);
	}
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
		if (get_bool(&(input->lock), input->philos[i].full) == true)
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
	while (!get_bool(&(input->lock), input->philos[i].die))
	{
		if (check_death(&(input->philos[i]), &(input->lock)) == 1)
		{
			print_action(&(input->lock), &input->philos[i],
				get_long(&(input->lock), &(input->philos[i].start->tv_sec)), DIE);
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
