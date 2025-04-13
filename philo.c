/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:25 by lformank          #+#    #+#             */
/*   Updated: 2025/04/12 13:33:53 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_input(t_input *input)
{
	int	i;

	i = -1;
	free(input->forks);
	while (++i < input->num_of_phil)
	{
		free(input->philos[i].full);
		free(input->philos[i].die);
		free(input->philos[i].ms);
		free(input->philos[i].philo);
		free(input->philos[i].lfork);
		free(input->philos[i].rfork);
		free(input->philos[i].start);
	}
	free((input)->philos);
}

int	main(int ac, char **av)
{
	t_input		input;

	if (!init(ac, av))
		return (0);
	if (!setup_input(ac, av, &input))
		return (0);
	if (!setup_forks(&input))
		return (0);
	if (!setup_philos(&input, ac, av))
		return (0);
	free_input(&input);
	return (0);
}
