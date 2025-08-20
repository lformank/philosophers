/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:14:25 by lformank          #+#    #+#             */
/*   Updated: 2025/08/20 13:08:44 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_philos(t_input *input, int ac, char *av[])
{
	long	i;

	i = -1;
	if (input->num_of_phil == 1)
	{
		input->philos[0].input = input;
		if (!setup_philo(&(input)->philos[0], 0, ac, av))
			return (0);
		if (pthread_create(input->philos[0].philo, NULL, &aroutine,
				&input->philos[0]))
		{
			printf("Failed to create thread\n");
			return (0);
		}
	}
	else if (!more_philos(input, ac, av))
		return (0);
	set_long(&(input->lock), input->start, now());
	set_bool(&(input->lock), &(input->ready), true);
	droutine(input);
	while (++i < input->num_of_phil)
		pthread_join(*(input)->philos[i].philo, NULL);
	return (1);
}

static int	malloc_philo(t_philo *philo)
{
	philo->philo = malloc(sizeof(pthread_t) * (philo->num_of_phil));
	if (!philo->philo)
		return (0);
	philo->last = malloc(sizeof(struct timeval) * 1);
	if (!philo->last)
		return (0);
	philo->last->tv_sec = 0;
	philo->die = false;
	philo->die = false;
	return (1);
}

int	setup_philo(t_philo *philo, int i, long ac, char *av[])
{
	philo->num = i + 1;
	philo->num_of_phil = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->num_of_meals = 0;
	if (ac == 6)
		philo->num_of_meals = ft_atoi(av[5]);
	if (!malloc_philo(philo))
		return (0);
	philo->rfork = &(philo->input->forks[philo->num - 1]);
	if (philo->num == philo->num_of_phil)
		philo->lfork = &(philo->input->forks[0]);
	else
		philo->lfork = &(philo->input->forks[philo->num]);
	if (pthread_mutex_init(&(philo->lock), NULL))
		return (0);
	set_bool(&(philo->lock), &(philo->full), false);
	set_bool(&(philo->lock), &(philo->die), false);
	return (1);
}

int	setup_forks(t_input *input)
{
	long	i;

	i = -1;
	input->forks = malloc((sizeof(pthread_mutex_t)) * (input->num_of_phil));
	if (!input->forks)
		return (0);
	while (++i < input->num_of_phil)
	{
		if (pthread_mutex_init(&(input->forks[i]), NULL))
		{
			free(input->forks);
			return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_input	input;

	if (!init(ac, av))
		return (1);
	if (!setup_input(ac, av, &input))
	{
		wrong_input(4);
		free_input(&input);
		return (1);
	}
	if (!setup_forks(&input))
	{
		wrong_input(5);
		free_input(&input);
		return (1);
	}
	if (!setup_philos(&input, ac, av))
	{
		wrong_input(6);
		free_input(&input);
		return (1);
	}
	free_input(&input);
	return (0);
}
