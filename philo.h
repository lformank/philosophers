/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:15:01 by lformank          #+#    #+#             */
/*   Updated: 2025/05/08 15:04:41 by lformank         ###   ########.fr       */
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
	bool			ready;
	pthread_mutex_t	read;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	struct s_death	*death;
}	t_input;



typedef struct s_philo
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				num;
	bool			*full;
	t_input			*input;
	pthread_t		*philo;
	pthread_mutex_t	*to_write;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	bool			*die;
	struct timeval	*start;
	struct timeval	*timer;
	struct timeval	*last;
}	t_philo;

typedef struct s_death
{
	t_philo		*philo;
	t_input		*input;
	pthread_t	*thread;
	bool		*ate;
}	t_death;

/* INICIALIZE */
int	init(int ac, char *av[]);
int	setup_input(int ac, char *av[], t_input *input);
int	setup_philos(t_input *input, int ac, char *av[]);
int	setup_philo(t_philo *philo, int i, int ac, char *av[]);
int	setup_forks(t_input *input);

/* UTILS */
int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);
void	now(struct timeval	*t);
void	free_input(t_input *input);
void	set_bool(pthread_mutex_t *lock, bool *variable, bool value);
bool	get_bool(pthread_mutex_t *lock, bool *variable);

/* CONDITIONS */
void	wrong_input(void);
int		is_it_num(char *av[], int ac);

/* ROUTINE */
void	*routine(void *input);
void	*droutine(void *table);
#endif