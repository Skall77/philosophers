/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:32:46 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 18:02:06 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*th;

	i = -1;
	th = malloc(sizeof(pthread_t) * (size_t)data->n_philos);
	if (!th)
		return (1);
	while (++i < data->n_philos)
	{
		if (pthread_create(&th[i], NULL, routine, (void *)&philo[i]))
		{
			while (i--)
				pthread_join(th[i], NULL);
			return ((void)free(th), 1);
		}
	}
	if (check_if_done(philo, data) != 0)
		return (destroy_mutex(philo, data, th, 1));
	i = -1;
	while (++i < data->n_philos)
		if (pthread_join(th[i], NULL))
			return (1);
	return (destroy_mutex(philo, data, th, 0));
}

int	destroy_mutex(t_philo *philo, t_data *data, pthread_t *th, int ret)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	i = 0;
	while (i < MUTEX_NUMBERS)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
	free (th);
	return (ret);
}

int	check_if_done(t_philo *philo, t_data *data)
{
	int				i;
	unsigned long	t_eat;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[EAT]);
		t_eat = philo[i].t_last_eat;
		pthread_mutex_unlock(&data->mutex[EAT]);
		if (t_eat && are_all_full(philo, data))
		{
			all_full(data);
			break ;
		}
		if (t_eat && get_time() - t_eat > (unsigned long)data->t_die)
		{
			all_dead(data);
			print_logs(philo, "died");
			break ;
		}
		i = (i + 1) % data->n_philos;
		usleep(200);
	}
	return (0);
}

int	are_all_full(t_philo *philo, t_data *data)
{
	int	i;
	int	full;
	int	meals_count;

	if (data->n_eat == -1)
		return (0);
	i = -1;
	full = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&philo->data->mutex[EAT]);
		meals_count = philo[i].meals_count;
		pthread_mutex_unlock(&philo->data->mutex[EAT]);
		if (meals_count >= data->n_eat)
			if (++full == data->n_philos -1)
				return (1);
		usleep(50);
	}
	return (0);
}
