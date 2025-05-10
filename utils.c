/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:12:14 by lformank          #+#    #+#             */
/*   Updated: 2025/05/10 16:12:07 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(pthread_mutex_t *lock, t_philo *philo, long int time,
	enum mode to_print)
{
	struct timeval	t;

	now(lock, &t);
	pthread_mutex_lock(lock);
	if (to_print == 0)
		printf("%ld %d has taken a fork\n", t.tv_sec - time, philo->num);
	else if (to_print == 1)
		printf("%ld %d is eating\n", t.tv_sec - time, philo->num);
	else if (to_print == 2)
		printf("%ld %d is sleeping\n", t.tv_sec - time, philo->num);
	else if (to_print == 3)
		printf("%ld %d is thinking\n", t.tv_sec - time, philo->num);
	else if (to_print == 4)
		printf("%ld %d died\n", t.tv_sec - time, philo->num);
	pthread_mutex_unlock(lock);
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

long int	get_long(pthread_mutex_t *lock, long int *variable)
{
	long int	value;

	pthread_mutex_lock(lock);
	value = *variable;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_long(pthread_mutex_t *lock, long int *variable, long int value)
{
	pthread_mutex_lock(lock);
	*variable = value;
	pthread_mutex_unlock(lock);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long int	n;
	int			minus;
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
