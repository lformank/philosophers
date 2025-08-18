/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:12:14 by lformank          #+#    #+#             */
/*   Updated: 2025/08/18 19:17:24 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(pthread_mutex_t *lock, t_philo *philo, long time,
	enum e_mode to_print)
{
	long	t;

	pthread_mutex_lock(lock);
	t = now();
	if (philo->input->dead == true && to_print != DIE)
	{
		pthread_mutex_unlock(lock);
		return ;
	}
	if (to_print == 0 && !get_bool(&(philo->lock), philo->die))
		printf("%ld %d has taken a fork\n", t - time, philo->num);
	else if (to_print == 1 && !get_bool(&(philo->lock), philo->die))
		printf("%ld %d is eating\n", t - time, philo->num);
	else if (to_print == 2 && !get_bool(&(philo->lock), philo->die))
		printf("%ld %d is sleeping\n", t - time, philo->num);
	else if (to_print == 3 && !get_bool(&(philo->lock), philo->die))
		printf("%ld %d is thinking\n", t - time, philo->num);
	else if (to_print == 4 && !get_bool(&(philo->lock), philo->die))
		printf("%ld %d died\n", t - time, philo->num);
	else if (to_print == 5 /*&& !get_bool(&(philo->lock), philo->die)*/)
		printf("%ld philosophers are full!\n", t - time);
	pthread_mutex_unlock(lock);
}

long	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	t.tv_sec = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (t.tv_sec);
}

void	free_input(t_input *input)
{
	int	i;

	i = -1;
	while (input->philos && ++i < input->num_of_phil)
	{
		free(input->philos[i].philo);
		free(input->philos[i].last);
		free(input->philos[i].die);
		free(input->philos[i].full);
		pthread_mutex_destroy(&(input->philos[i].lock));
	}
	if (input->philos)
		free(input->philos);
	i = -1;
	while (input->forks && ++i < input->num_of_phil)
		pthread_mutex_destroy(&(input->forks[i]));
	if (input->forks)
		free(input->forks);
	pthread_mutex_destroy(&(input->lock));
	free(input->start);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *nptr)
{
	int		i;
	long	n;
	int		no_num;

	i = -1;
	n = 0;
	no_num = true;
	while (nptr[++i])
	{
		if (nptr[i] == '-')
			break ;
		if (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
		{
			n = (n * 10) + (nptr[i] - 48);
			no_num = false;
		}
	}
	if (no_num == true || n > 2147483647 || n < -2147483648)
	{
		wrong_input(2);
		return (-1);
	}
	return (n);
}
