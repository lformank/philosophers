/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/08/16 17:35:24 by lformank         ###   ########.fr       */
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

# define RES	"\033[0m"
# define R		"\033[31m"

enum	e_mode
{
	FORKING,
	EATING,
	SLEEPING,
	THINKING,
	DIE
};

typedef struct s_input
{
	long			num_of_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_meals;
	bool			ready;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	struct s_death	*death;
	bool			*ate;
	bool			*dead;
}	t_input;

typedef struct s_philo
{
	long				num;
	long				num_of_phil;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_of_meals;
	enum e_mode		action;
	t_input			*input;
	pthread_t		*philo;
	pthread_mutex_t	lock;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	bool			*die;
	bool			*full;
	struct timeval	*start;
	struct timeval	*timer;
	struct timeval	*last;
}	t_philo;

/* INICIALIZE */
long			init(long ac, char *av[], t_input *input);
long			setup_input(long ac, char *av[], t_input *input);
long			setup_philos(t_input *input, long ac, char *av[]);
long			setup_philo(t_philo *philo, long i, long ac, char *av[]);
long			setup_forks(t_input *input);

/* UTILS */
long			ft_atoi(const char *nptr);
long			ft_strlen(const char *s);
long	now(pthread_mutex_t *lock, struct timeval *t);
void		get_time(t_philo *philo, struct timeval *t);
void		free_input(t_input *input);
void		set_bool(pthread_mutex_t *lock, bool *variable, bool value);
bool		get_bool(pthread_mutex_t *lock, bool *variable);
long	get_long(pthread_mutex_t *lock, long *variable);
void		set_long(pthread_mutex_t *lock, long *variable, long value);
void		print_action(pthread_mutex_t *lock, t_philo *philo, long time,
				enum e_mode action);

/* CONDITIONS */
void		wrong_input(void);
long			is_it_num(char *av[], long ac);

/* ROUTINE */
void	*routine(void *input);
void	droutine(t_input *input);
#endif