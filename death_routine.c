/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/04/27 16:30:03 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->num_of_phil)
	{
		*(input)->philos[i].die = true;
		// free_input(input);
	}
}

int	check_death(t_input *input, int *i)
{
	struct timeval	t;
	long int		time_till_eat;

	now(&t);
	time_till_eat = t.tv_sec - input->philos[*i].last->tv_sec;
	if (time_till_eat >= input->philos[*i].time_to_die)
	{
		*(input)->philos[*i].die = true;
		return (1);
	}
	return (0);
}

void	*droutine(void *table)
{
	t_input			input;
	int				i;
	struct timeval	t;

	i = -1;
	input = *(t_input *)table;
	while (*(input).philos[++i].die == false)
	{
		while (++i < input.num_of_phil)
		{
			if (check_death(&input, &i) == 1)
			{
				kill_philos(&input);
				now(&t);
				printf("%ld %d died\n", t.tv_sec - (input).philos[i].start->tv_sec, i);
				return (0);
			}
			// TODO if all of them eat
		}
		i = -1;
	}
	return (table);
}
