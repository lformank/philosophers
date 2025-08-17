/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 18:56:35 by lformank         ###   ########.fr       */
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

int	check_death(t_input *input)
{
	long	t;
	long	since_last;
	int		i;

	i = 0;
	while (i <= input->num_of_phil)
	{
		t = now();
		since_last = t - get_long(&(input->philos[i].lock), &(input->philos[i].last->tv_sec));
		if (since_last >= input->time_to_die)
			return (i);
		i++;
	}
	return (-1);
}

int	check_meals(t_input *input)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (input->num_of_meals == 0)
		return (0);
	while (++i < input->num_of_phil)
	{
		if (get_bool(&(input->philos[i].lock), input->philos[i].full) == true)
			count++;
		if (count == input->num_of_phil)
			return (1);
	}
	return (0);
}

void	droutine(t_input *input)
{
	long	start;
	int		dead_i;

	while (1)
	{
		dead_i = check_death(input);
		if (dead_i != -1)
		{
			start = get_long(&(input->lock), input->start);
			print_action(&(input->lock), &input->philos[dead_i], start, DIE);
			kill_philos(input);
			break ;
		}
		if (check_meals(input) == 1)
		{
			kill_philos(input);
			break ;
		}
		usleep(1000);
	}
	// free_input(input);
}
