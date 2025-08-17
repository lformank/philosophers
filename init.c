/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:17 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 11:39:34 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	setup_forks(t_input *input)
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

long	malloc_philo(t_philo *philo)
{
	philo->philo = malloc(sizeof(pthread_t) * (philo->num_of_phil));
	if (!philo->philo)
		return (0);
	philo->timer = malloc(sizeof(struct timeval) * 1);
	if (!philo->timer)
		return (0);
	philo->start = malloc(sizeof(struct timeval) * 1);
	if (!philo->start)
		return (0);
	philo->last = malloc(sizeof(struct timeval) * 1);
	if (!philo->last)
		return (0);
	philo->die = malloc(sizeof(bool) * 1);
	if (!philo->die)
		return (0);
	philo->full = malloc(sizeof(bool) * 1);
	if (!philo->full)
		return (0);
	return (1);
}

long	setup_philo(t_philo *philo, long i, long ac, char *av[])
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
	pthread_mutex_init(&(philo->lock), NULL);
	pthread_mutex_init(&(philo->lock_last), NULL);
	set_bool(&(philo->lock), (philo)->full, false);
	set_bool(&(philo->lock), (philo)->die, false);
	return (1);
}

void	*lone_routine(void *philos)
{
	t_philo	philo;
	struct timeval	t;

	philo = *(t_philo *)philos;
	while (!get_bool(&(philo.lock), &(philo.input->ready)))
		;
	get_time(&philo, &t);
	now(&(philo.lock), philo.start);
	now(&(philo.lock), philo.last);
	usleep(philo.time_to_die / 2);
	while (t.tv_sec - philo.start->tv_sec < philo.time_to_sleep &&
		!get_bool(&(philo.lock), philo.die))
		now(&(philo.lock), &t);
	return (philos);
}

int	setup_philos(t_input *input, long ac, char *av[])
{
	long	i;

	i = -1;
	if (input->num_of_phil == 1)
	{
		input->philos[0].input = input;
		setup_philo(&(input)->philos[0], 0, ac, av);
		pthread_create(input->philos[0].philo, NULL, &lone_routine, input->philos);
	}
	else
	{
		while (++i < input->num_of_phil)
		{
			input->philos[i].input = input;
			if (!setup_philo(&(input)->philos[i], i, ac, av)
				|| pthread_create(input->philos[i].philo, NULL,
					&routine, &input->philos[i]))
			{
				free_input(input);
				printf("Failed to create thread\n");
				return (0);
			}
		}
	}
	set_bool(&(input->lock), &input->ready, true);
	while (--i >= 0)
		pthread_join(*(input)->philos[i].philo, NULL);
	droutine(input);
	free_input(input);
	return (1);
}

long	setup_input(long ac, char *av[], t_input *input)
{
	input->num_of_phil = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->num_of_meals = 0;
	if (ac == 6)
		input->num_of_meals = ft_atoi(av[5]);
	input->ready = false;
	input->philos = malloc(sizeof(t_philo) * (input->num_of_phil));
	if (!input->philos)
		return (0);
	input->ate = false;
	input->dead = false;
	pthread_mutex_init(&(input->lock), NULL);
	return (1);
}

long	init(long ac, char *av[], t_input *input)
{
	if (ac < 5 || ac > 6)
	{
		wrong_input();
		return (0);
	}
	if (ft_atoi(av[1]) == 0)
		return (0);
	if (av[5])
		if (ft_atoi(av[5]) == 0)
			return (0);
	if (!is_it_num(av, ac))
	{
		wrong_input();
		return (0);
	}
	input = malloc(1 * sizeof(t_input));
	if (!input)
	{
		printf("Error in allocating!");
		return (0);
	}
	return (1);
}
