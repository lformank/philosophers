/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/05/08 11:38:36 by lformank         ###   ########.fr       */
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
	struct timeval t;
	long int		time_since_meal;

	now(&t);
	time_since_meal = t.tv_sec - input->philos[*i].last->tv_sec;
	if (time_since_meal >= input->philos[*i].time_to_die )
	{
		*(input)->philos[*i].die = true;
		return (1);
	}
	return (0);
}

int	check_meals(t_input *input, int *i)
{
	if (*(input)->philos[*i].full == input->num_of_meals)
	{
		*(input)->philos[*i].die = true;
		// kill_philos(input);
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
		while (i < input.num_of_phil && *(input).philos[i].die == false)
		{
			if (check_death(&input, &i) == 1)
			{
				kill_philos(&input);
				now(&t);
				printf("%ld %d died\n", t.tv_sec - input.philos[i].start->tv_sec, input.philos[i].num);
				return (0);
			}
			if (input.num_of_meals && check_meals(&input, &i) == 1)
			{
				kill_philos(&input);
				return (0);
			}
			i++;
		}
		i = -1;
	}
	return (table);
}
