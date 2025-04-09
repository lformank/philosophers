/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:17 by lformank          #+#    #+#             */
/*   Updated: 2025/04/09 16:41:27 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_it_num(char *av[], int ac)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (++i < ac && av[i])
	{
		j = -1;
		while (av[i][++j] && j < ft_strlen(av[i]))
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '-'
				&& av[i][j] != '+')
				return (0);
			if (av[i][j] >= '0' && av[i][j] <= '9')
				num = 1;
			if ((av[i][j] == '+' || av[i][j] == '-') && num == 1)
				return (0);
			if ((av[i][j] == '+' || av[i][j] == '-')
				&& (av[i][j + 1] == '+' || av[i][j + 1] == '-'))
				return (0);
		}
	}
	return (1);
}

void	wrong_input(void)
{
	write(2, "Wrong input.\nTry again using this format: \"./philo <num of \
philosophers> <time to die> <time to eat> <time to sleep> <number of \
meals>\"", 141);
	return ;
}

void	*routine(void *input)
{
	int	i;
	t_input	table;

	i = 0;
	table = *(t_input *)input;
	while(i < table.num_of_philo)
	{
		table.philos->num = i++;
		printf("shit n%d\n", i);
	}
	return (0);
}

int	setup_forks(t_input *input)
{
	int	i;

	i = -1;
	input->forks = malloc((sizeof(bool)) * input->num_of_philo);
	input->forks[4] = 0;
	input->forks[3] = 1;
	input->forks[2] = 0;
	input->forks[1] = 1;
	input->forks[0] = 0;
	while (++i < 5)
		printf("forks[%d]: %d\n", i, input->forks[i]);
	return (1);
}

int	setup_philos(t_input *input)
{
	int	i;
	
	i = -1;
	input->philos = malloc(sizeof(t_philo) * input->num_of_philo);
	if (!input->philos)
		return (0);
	while (++i < input->num_of_philo)
	{
		input->philos[i].philo = malloc(sizeof(pthread_t) * input->num_of_philo);
		if (pthread_create((input->philos[i].philo), NULL, &routine, input)) 
		{
			printf("Failed to create thread\n");
			return (0);
		}
	}
	i = -1;
	while (++i < input->num_of_philo)
	{
		if (pthread_join(*(input->philos[i].philo), NULL))
		{
			printf("Failed to create thread\n");
			return (0);
		}
	}
	return (1);
}

void	setup_time(t_input *input)
{
	gettimeofday(&(input)->start, NULL);
	input->start.tv_usec /= 1000;
	printf("s: %ld\tus: %ld\n", input->start.tv_sec, input->start.tv_usec);
}

int	setup_input(int ac, char *av[], t_input *input)
{
	input->num_of_philo = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->num_of_meals = ft_atoi(av[5]);
	setup_time(input);
	return (1);
}

int	init(int ac, char *av[], t_input *input)
{
	if (ac < 5 || ac > 6)
	{
		wrong_input();
		return (0);
	}
	if (*av[1] == '0')
		return (0);
	if (!is_it_num(av, ac))
	{
		wrong_input();
		return (0);
	}
	if (!setup_input(ac, av, input))
		return (0);
	if (!setup_forks(input))
		return (0);
	if (!setup_philos(input))
		return (0);
	return (1);
}
