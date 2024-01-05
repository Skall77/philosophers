/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:43:37 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:43:27 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

unsigned long	relative_time(unsigned long time)
{
	unsigned long	current_time;

	current_time = get_time();
	return (current_time - time);
}

void	smart_sleep(unsigned long m_seconds)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		usleep(m_seconds * 50);
		i++;
	}
}
