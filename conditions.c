/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:01:09 by lformank          #+#    #+#             */
/*   Updated: 2025/05/10 11:19:57 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wrong_input(void)
{
	write(2, "Wrong input.\nTry again using this format: \"./philo <num of \
philosophers> <time to die> <time to eat> <time to sleep> <number of \
meals>\"", 136);
	return ;
}

int	is_it_num(char *av[], int ac)
{
	int	i;
	int	j;
	int	num;

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
