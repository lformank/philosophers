/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/08/18 21:29:11 by lformank         ###   ########.fr       */
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
	SLEEP,
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
	bool			dead;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	long			*start;
}	t_input;

typedef struct s_philo
{
	int				num;
	int				num_of_phil;
	long			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	t_input			*input;
	pthread_t		*philo;
	pthread_mutex_t	lock;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	bool			*die;
	bool			*full;
	struct timeval	*last;
}	t_philo;

/* INICIALIZE */
int				init(long ac, char *av[]);
int				setup_input(long ac, char *av[], t_input *input);
int				setup_philos(t_input *input, int ac, char *av[]);
int				setup_philo(t_philo *philo, int i, long ac, char *av[]);
int				setup_forks(t_input *input);
void			*aroutine(void *philos);
int				more_philos(t_input *input, int ac, char *av[]);

/* UTILS */
long			ft_atoi(const char *nptr);
int				ft_strlen(const char *s);
long			now(void);
void			free_input(t_input *input);
void			set_bool(pthread_mutex_t *lock, bool *variable, bool value);
void			set_long(pthread_mutex_t *lock, long *variable, long value);
bool			get_bool(pthread_mutex_t *lock, bool *variable);
long			get_long(pthread_mutex_t *lock, long *variable);
void			print_action(pthread_mutex_t *lock, t_philo *philo, long time,
					enum e_mode action);

/* CONDITIONS */
void			wrong_input(int error);
long			is_it_num(char *av[], long ac);

/* ROUTINE */
void			*routine(void *input);
void			droutine(t_input *input);
#endif