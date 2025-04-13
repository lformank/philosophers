/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/04/12 15:51:12 by lformank         ###   ########.fr       */
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
# include <time.h>

typedef struct s_input
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	bool			*forks;
	struct s_philo	*philos;
	pthread_t		death;
}	t_input;

typedef struct s_philo
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				num;
	t_input			*table;
	pthread_t		*philo;
	bool			*lfork;
	bool			*rfork;
	bool			*die;
	bool			*full;
	struct timeval	*ms;
	struct timeval	*start;
	struct timeval	*ate;
	pthread_mutex_t	lock;
}	t_philo;

/* INICIALIZE */
int	init(int ac, char *av[]);
int	setup_input(int ac, char *av[], t_input *input);
int	setup_philos(t_input *input, int ac, char *av[]);
int	setup_philo(t_philo *philo, int i, int ac, char *av[]);
int	setup_forks(t_input *input);

/* UTILS */
int	ft_atoi(const char *nptr);
int	ft_strlen(const char *s);

/* CONDITIONS */
void	wrong_input(void);
int		is_it_num(char *av[], int ac);

/* ROUTINE */
void	*routine(void *input);
#endif