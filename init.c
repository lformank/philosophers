/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:17 by lformank          #+#    #+#             */
/*   Updated: 2025/04/12 16:06:07 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_forks(t_input *input)
{
	int	i;

	i = -1;
	input->forks = malloc((sizeof(bool)) * (input->num_of_phil));
	while (++i < input->num_of_phil)
		input->forks[i] = 1;
	return (1);
}

int	setup_philo(t_philo *philo, int i, int ac, char *av[])
{
	philo->num = i + 1;
	philo->num_of_phil = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	philo->num_of_meals = ft_atoi(av[5]);
	philo->philo = malloc(sizeof(pthread_t) * (philo->num_of_phil));
	philo->ms = malloc(sizeof(struct timeval) * 1);
	philo->start = malloc(sizeof(struct timeval) * 1);
	philo->ate = malloc(sizeof(struct timeval) * 1);
	philo->lfork = malloc(sizeof(bool) * 1);
	*(philo)->lfork = 0;
	philo->rfork = malloc(sizeof(bool) * 1);
	*(philo)->rfork = 0;
	philo->die = malloc(sizeof(int) * 1);
	*(philo)->die = 0;
	philo->full = malloc(sizeof(int) * 1);
	*(philo)->full = 0;

	if (!philo->philo || !philo->ms || !philo->die || !philo->full
		|| !philo->lfork || !philo->rfork || !philo->start)
		return (0);
	return (1);
}
	
int	setup_philos(t_input *input, int ac, char *av[])
{
	int	i;
	
	i = -1;
	input->philos = malloc(sizeof(t_philo) * (input->num_of_phil));
	if (!input->philos)
		return (0);
	while (++i < input->num_of_phil)
	{
		input->philos[i].table = input; /*malloc(sizeof(t_input) * 1);
		input->philos->table = input;*/
		if (!setup_philo(&(input)->philos[i], i, ac, av)
			|| pthread_create((input->philos[i].philo), NULL,
			&routine, &(input->philos[i])))
		{
			free(input);
			printf("Failed to create thread\n");
			return (0);
		}
	}
	// TODO - it frees the threads
	while (--i >= 0)
	{
		if (pthread_join(*(input->philos[i].philo), NULL))
		{
			printf("Failed to join thread\n");
			return (0);
		}
	}
	return (1);
}

int	setup_input(int ac, char *av[], t_input *input)
{
	input->num_of_phil = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->num_of_meals = ft_atoi(av[5]);
	return (1);
}

int	init(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
	{
		wrong_input();
		return (0);
	}
	if (ft_atoi(av[1]) == 0)
		return (0);
	if (!is_it_num(av, ac))
	{
		wrong_input();
		return (0);
	}
	return (1);
}
