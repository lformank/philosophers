/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/04/09 16:41:25 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_input
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	bool			*forks;
	struct s_philo	*philos;
	struct timeval	start;
}	t_input;

typedef struct s_philo
{
	int			num;
	pthread_t	*philo;
	bool		*lfork;
	bool		*rfork;
	bool		die;
}	t_philo;

/* INICIALIZE */
int	init(int ac, char *av[], t_input *input);

/* UTILS */
int	ft_atoi(const char *nptr);
int	ft_strlen(const char *s);

#endif