/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/16 17:38:53 by lformank         ###   ########.fr       */
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

long	check_death(t_input *input, long *i)
{
	struct timeval	t;

	if (now(&(input->lock), &t) - get_long(&(input->lock),
			&(input->philos[*i].last->tv_sec)) >= get_long(&(input->lock), &input->time_to_die))
	{
		set_bool(&(input->lock), input->philos[*i].die, true);
		return (1);
	}
	return (0);
}

long	check_meals(t_input *input)
{
	long	i;
	long	count;

	i = -1;
	count = 0;
	while (++i < input->num_of_phil)
	{
		if (get_bool(&(input->lock), input->philos[i].full) == true)
			count++;
		if (count == input->num_of_phil)
			return (1);
	}
	return (0);
}

void	droutine(t_input *input)
{
	long		i;

	i = -1;
	while (!get_bool(&(input->lock), input->philos[++i].die))
	{
		if (check_death(input, &i) == 1)
		{
			print_action(&(input->lock), &input->philos[i],
				input->philos[i].start->tv_sec, DIE);
			kill_philos(input);
			return ;
		}
		if (check_meals(input) == 1)
			kill_philos(input);
		if (i == input->num_of_phil - 1)
			i = -1;
	}
	free_input(input);
}
