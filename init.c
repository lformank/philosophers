/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:17 by lformank          #+#    #+#             */
/*   Updated: 2025/08/20 12:47:27 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*aroutine(void *philos)
{
	t_philo	*philo;
	long	since_start;

	philo = (t_philo *)philos;
	while (!get_bool(&(philo->input->lock), &(philo->input->ready)))
		;
	set_long(&(philo->lock), &(philo->last->tv_sec), now());
	since_start = now();
	usleep((philo->time_to_die / 2) * 1000);
	while (now() - since_start < philo->time_to_die && !get_bool(&(philo->lock),
			&(philo->die)))
		;
	return (philos);
}

int	more_philos(t_input *input, int ac, char *av[])
{
	int	i;

	i = -1;
	while (++i < input->num_of_phil)
	{
		input->philos[i].input = input;
		if (!setup_philo(&(input)->philos[i], i, ac, av)
			|| pthread_create(input->philos[i].philo, NULL,
				&routine, &input->philos[i]))
		{
			write(2, "Failed to create thread\n", 24);
			return (0);
		}
	}
	return (1);
}

int	setup_input(long ac, char *av[], t_input *input)
{
	input->num_of_phil = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->num_of_meals = 0;
	if (ac == 6)
		input->num_of_meals = ft_atoi(av[5]);
	input->ready = false;
	input->dead = false;
	input->philos = malloc(sizeof(t_philo) * (input->num_of_phil));
	if (!input->philos)
		return (0);
	input->start = malloc(sizeof(long) * 1);
	if (!input->start)
		return (0);
	pthread_mutex_init(&(input->lock), NULL);
	return (1);
}

int	init(long ac, char *av[])
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		wrong_input(1);
		return (0);
	}
	if (ft_atoi(av[1]) == 0)
		return (0);
	if (av[5])
		if (ft_atoi(av[5]) == 0)
			return (0);
	while (++i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (0);
	}
	if (!is_it_num(av, ac))
	{
		wrong_input(3);
		return (0);
	}
	return (1);
}
