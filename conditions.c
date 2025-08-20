/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/08/20 12:37:45 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wrong_input(int error)
{
	if (error == 1)
	{
		write(2, "Wrong number of arguments.\n", 27);
		write(2, "Try again using this format: \"./philo <num of philosophers>\
 <time to die> <time to eat> <time to sleep> <number of meals>\".\n", 125);
	}
	else if (error == 2)
		write(2, "Invalid argument. Arguments have to be in positive numeric \
format and have max size of int.\n", 93);
	else if (error == 3)
		write(2, "Arguments are not numbers. Write them in ms format.\n", 52);
	return ;
}

long	is_it_num(char *av[], long ac)
{
	long	i;
	long	j;
	long	num;

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
