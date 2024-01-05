/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:32:55 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:26:21 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_full(t_data *data)
{
	pthread_mutex_lock(&data->mutex[FULL]);
	data->all_full = 1;
	pthread_mutex_unlock(&data->mutex[FULL]);
}

void	all_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex[DEAD]);
	data->dead = 1;
	pthread_mutex_unlock(&data->mutex[DEAD]);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex[DEAD]));
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&(philo->data->mutex[DEAD]));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->mutex[DEAD]));
	return (0);
}

int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex[FULL]));
	if (philo->data->all_full)
	{
		pthread_mutex_unlock(&(philo->data->mutex[FULL]));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->mutex[FULL]));
	return (0);
}

void	print_logs(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->data->mutex[LOGS]));
	if (*str == 'd' || (!is_dead(philo) && !is_full(philo)))
		printf("%lu %d %s\n", relative_time(philo->data->basetime),
			philo->id, str);
	pthread_mutex_unlock(&(philo->data->mutex[LOGS]));
}
