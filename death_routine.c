/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/04/30 16:56:48 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_ready(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->num_of_phil)
		*(input)->philos[i].set = true;
}

void	check_ready(t_input *input)
{
	int	i;

	i = -1;
	while (!*(input)->death->ready)
	{
		while (++i < input->num_of_phil)
		{
			if (input->philos[i].ready)
				*(input)->death->ready += 1;
		}
		i = -1;
		if (*(input)->death->ready == input->num_of_phil - 1)
		{
			set_ready(input);
			break;
		}
		else
			*(input)->death->ready = 0;
	}
}

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
	printf("%d\n", *(input)->philos[*i].full);
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
	check_ready(&input);
	printf("%d\n", *(input).philos[i].full);
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
			if (check_meals(&input, &i) == 1)
				return (0);
		}
		i = -1;
	}
	return (table);
}
