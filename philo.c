/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:25 by lformank          #+#    #+#             */
/*   Updated: 2025/08/16 16:34:52 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	free_input(t_input *input)
{
	free(input);
}

int	main(int ac, char **av)
{
	t_input	input;

	if (!init(ac, av, &input))
		return (0);
	if (!setup_input(ac, av, &input))
	{
		free_input(&input);
		return (0);
	}
	if (!setup_forks(&input))
	{
		free_input(&input);
		return (0);
	}
	if (!setup_philos(&input, ac, av))
	{
		free_input(&input);
		return (0);
	}
	return (0);
}
