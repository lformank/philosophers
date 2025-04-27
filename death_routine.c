/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:12 by lformank          #+#    #+#             */
/*   Updated: 2025/04/26 19:16:35 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_philos(t_input *input)
{

}

int	check_death(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->num_of_phil)
	{
		if (input->philos[i].time_to_die < input->philos[i].timer) //TODO
		{
			
		}
	}
}

void	droutine(void *table)
{
	t_input	input;
	int		i;

	i = 0;
	input = *(t_input *)table;
	while (!input.death->dead)
	{
		while (i < input.num_of_phil)
		{
			if (check_death(&input) == 1)
			{
				kill_philos(&input); // TODO
				return (0);
			}
			//TODO if all of them eat
		}
		i = 0;
	}
}
