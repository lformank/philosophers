/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/05/18 17:05:33 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->num_of_phil)
		set_bool(input->death->lock, &input->philos[i].die, true);
}

int	check_death(t_input *input, int *i)
{
	struct timeval	t;

	if (now(input->death->lock, &t) - get_long(input->death->lock,
			&input->philos[*i].last->tv_sec) >= input->time_to_die)
	{
		set_bool(input->death->lock, &input->philos[*i].die, true);
		return (1);
	}
	return (0);
}

int	check_meals(t_input *input)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < input->num_of_phil)
	{
		if (get_bool(input->death->lock, &input->philos[i].full) == true)
		{
			count++;
			printf("meals = %d\n", count);
		}
		if (count == input->num_of_phil)
			return (1);
	}
	return (0);
}

void	*droutine(void *table)
{
	t_input	input;
	int		i;

	i = -1;
	input = *(t_input *)table;
	while (!get_bool(input.death->death_lock, &input.philos[++i].die))
	{
		if (check_death(&input, &i) == 1)
		{
			print_action(input.death->lock, &input.philos[i],
				input.philos[i].start->tv_sec, DIE);
			kill_philos(&input);
			return (0);
		}
		if (check_meals(&input) == 1)
			kill_philos(&input);
		printf("hey\n");
		if (i == input.num_of_phil - 1)
			i = -1;
	}
	return (table);
}
