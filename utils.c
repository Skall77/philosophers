/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:11:46 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:32:02 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	message_error(char *str, int n)
{
	printf("%s", str);
	return (n);
}

long	ft_atoi_long(char *nptr)
{
	int		i;
	long	sign;
	long	atoi;

	i = 0;
	sign = 1;
	atoi = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		atoi = atoi * 10 + nptr[i] - '0';
		i++;
	}
	return (atoi * sign);
}

int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
