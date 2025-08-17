/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 17:07:13 by lformank         ###   ########.fr       */
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
	struct timeval	t;
	long			since_last;
	int				i;

	i = -1;
	while (++i < input->num_of_phil)
	{
		t.tv_sec = now();
		since_last = t.tv_sec - get_long(&(input->philos[i].lock_last), &(input->philos[i].last->tv_sec));
		if (since_last >= input->time_to_die)
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
	long	i;
	long	start;

	i = 0;
	while (1)
	{
		if (check_death(input) == 1)
		{
			start = get_long(&(input->philos[i].lock),
				&input->philos[i].start->tv_sec);
			print_action(&(input->lock), &input->philos[i], start, DIE);
			kill_philos(input);
			break ;
		}
		if (check_meals(input) == 1)
		{
			kill_philos(input);
			break ;
		}
		if (i == input->num_of_phil)
			i = 0;
		i++;
	}
	// free_input(input);
}
