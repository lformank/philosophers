/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:12:14 by lformank          #+#    #+#             */
/*   Updated: 2025/04/06 12:40:26 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			minus = -1;
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
