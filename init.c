/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:17 by lformank          #+#    #+#             */
/*   Updated: 2025/04/30 16:42:18 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_forks(t_input *input)
{
	int	i;

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

int	malloc_philo(t_philo *philo)
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
	philo->lfork = malloc(sizeof(pthread_mutex_t) * 1);
	if (!philo->lfork)
		return (0);
	philo->rfork = malloc(sizeof(pthread_mutex_t) * 1);
	if (!philo->rfork)
		return (0);
	philo->die = malloc(sizeof(int) * 1);
	if (!philo->die)
		return (0);
	philo->full = malloc(sizeof(int) * 1);
	if (!philo->full)
		return (0);
	return (1);
}

int	setup_philo(t_philo *philo, int i, int ac, char *av[])
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
	(philo)->lfork = &(philo)->input->forks[philo->num - 1];
	if (philo->num == philo->num_of_phil)
		(philo)->rfork = &(philo)->input->forks[0];
	else
		(philo)->rfork = &(philo)->input->forks[philo->num];
	*(philo)->die = 0;
	*(philo)->full = 0;
	philo->set = malloc(sizeof(int) * 1);
	if (!philo->set)
		return (0);
	philo->ready = false;
	now(philo->last);
	return (1);
}
	
int	setup_philos(t_input *input, int ac, char *av[])
{
	int	i;
	
	i = -1;
	while (++i < input->num_of_phil)
	{
		input->philos[i].input = input;
		if (!setup_philo(&(input)->philos[i], i, ac, av)
			|| pthread_create((input->philos[i].philo), NULL,
			&routine, &(input->philos[i])))
		{
			free(input);
			printf("Failed to create thread\n");
			return (0);
		}
		input->philos[i].ready = true;
	}
	if (pthread_create((input)->death->thread, NULL, &droutine, input))
	{
		free(input);
		printf("Failed to create thread\n");
		return (0);
	}
	while (--i >= 0)
		pthread_join(*(input->philos[i].philo), NULL);
	pthread_join(*(input)->death->thread, NULL);
	return (1);
}

int	setup_input(int ac, char *av[], t_input *input)
{
	input->num_of_phil = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->num_of_meals = 0;
	if (ac == 6)
		input->num_of_meals = ft_atoi(av[5]);
	input->philos = malloc(sizeof(t_philo) * (input->num_of_phil));
	if (!input->philos)
		return (0);
	input->death = malloc(sizeof(t_death) * 1);
	if (!input->death)
		return (0);
	input->death->thread = malloc(sizeof(pthread_t) * 1);
	if (!input->death->thread)
		return (0);
	input->death->ate = malloc(sizeof(int) * 1);
	if (!input->death->ate)
		return (0);
	*(input)->death->ate = false;
	input->death->ready = malloc(sizeof(int) * 1);
	if (!input->death->ready)
		return (0);
	*(input)->death->ready = false;
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
