/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:12:14 by lformank          #+#    #+#             */
/*   Updated: 2025/08/17 14:31:02 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(pthread_mutex_t *lock, t_philo *philo, long time,
	enum e_mode to_print)
{
	struct timeval	t;

	pthread_mutex_lock(lock);
	t.tv_sec = now();
	if (to_print == 4 && get_bool(&(philo->lock), philo->die) == true)
	{
		printf("%ld %d died\n", t.tv_sec - time, philo->num);
		return ;
	}
	else if (to_print == 1)
		printf("%ld %d is eating\n", t.tv_sec - time, philo->num);
	else if (to_print == 2)
		printf("%ld %d is sleeping\n", t.tv_sec - time, philo->num);
	else if (to_print == 3)
		printf("%ld %d is thinking\n", t.tv_sec - time, philo->num);
	else if (to_print == 0)
		printf("%ld %d has taken a fork\n", t.tv_sec - time, philo->num);
	pthread_mutex_unlock(lock);
}

struct timeval	get_timeval(pthread_mutex_t *lock, struct timeval *time)
{
	struct timeval	temp;

	pthread_mutex_lock(lock);
	temp = *time;
	pthread_mutex_unlock(lock);
	return (temp);
}

bool	get_bool(pthread_mutex_t *lock, bool *variable)
{
	bool	value;

	pthread_mutex_lock(lock);
	value = *variable;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_bool(pthread_mutex_t *lock, bool *variable, bool value)
{
	pthread_mutex_lock(lock);
	*variable = value;
	pthread_mutex_unlock(lock);
}

long	get_long(pthread_mutex_t *lock, long *variable)
{
	long	value;

	pthread_mutex_lock(lock);
	value = *variable;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_long(pthread_mutex_t *lock, long *variable, long value)
{
	pthread_mutex_lock(lock);
	*variable = value;
	pthread_mutex_unlock(lock);
}

long	ft_strlen(const char *s)
{
	long	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *nptr)
{
	long			i;
	long	n;
	long			minus;
	bool		no_num;

	i = -1;
	n = 0;
	minus = 1;
	no_num = true;
	while (nptr[++i])
	{
		if (nptr[i] == '-')
			return (0);
		if (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
		{
			n = (n * 10) + (nptr[i] - 48);
			no_num = false;
		}
	}
	if (no_num == true || (n * minus) > 2147483647 || (n * minus) < -2147483648)
		return (0);
	return (n * minus);
}
