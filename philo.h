/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/05/16 13:25:40 by lformank         ###   ########.fr       */
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
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	bool			ready;
	pthread_mutex_t	prt;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	struct s_death	*death;
}	t_input;

typedef struct s_philo
{
	int				num;
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	enum e_mode		action;
	t_input			*input;
	pthread_t		*philo;
	pthread_mutex_t	check;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	bool			die;
	bool			full;
	struct timeval	*start;
	struct timeval	*timer;
	struct timeval	*last;
}	t_philo;

typedef struct s_death
{
	t_philo			*philo;
	t_input			*input;
	pthread_t		*thread;
	bool			*ate;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*lock;
}	t_death;

/* INICIALIZE */
int			init(int ac, char *av[], t_input *input);
int			setup_input(int ac, char *av[], t_input *input);
int			setup_philos(t_input *input, int ac, char *av[]);
int			setup_philo(t_philo *philo, int i, int ac, char *av[]);
int			setup_forks(t_input *input);

/* UTILS */
int			ft_atoi(const char *nptr);
int			ft_strlen(const char *s);
long int	now(pthread_mutex_t *lock, struct timeval *t);
void		free_input(t_input *input);
void		set_bool(pthread_mutex_t *lock, bool *variable, bool value);
bool		get_bool(pthread_mutex_t *lock, bool *variable);
long int	get_long(pthread_mutex_t *lock, long int *variable);
void		set_long(pthread_mutex_t *lock, long int *variable, long int value);
void		print_action(pthread_mutex_t *lock, t_philo *philo, long int time,
				enum e_mode action);

/* CONDITIONS */
void		wrong_input(void);
int			is_it_num(char *av[], int ac);

/* ROUTINE */
void		*routine(void *input);
void		*droutine(void *table);
#endif