/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:21:00 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:30:43 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_philo **philo, t_data **data, int argc, char **argv)
{
	*data = malloc(sizeof (t_data));
	if (!*data)
		return (1);
	(*data)->mutex = NULL;
	if (init_data(data, argc, argv) != 0)
		return (1);
	*philo = malloc (sizeof(t_philo) * (size_t)(*data)->n_philos);
	if (!*philo)
		return (1);
	(*philo)->fork = NULL;
	if (init_philo(philo, *data) != 0)
		return (1);
	return (0);
}

int	init_data(t_data **data, int argc, char **argv)
{
	(*data)->basetime = get_time();
	(*data)->n_philos = (int)ft_atoi_long(argv[1]);
	(*data)->t_die = (int)ft_atoi_long(argv[2]);
	(*data)->t_eat = (int)ft_atoi_long(argv[3]);
	(*data)->t_sleep = (int)ft_atoi_long(argv[4]);
	(*data)->t_think = 0;
	if (((*data)->n_philos % 2) && ((*data)->t_eat > (*data)->t_sleep))
		(*data)->t_think = 1 + ((*data)->t_eat - (*data)->t_sleep);
	if (argc == 5)
		(*data)->n_eat = -1;
	if (argc == 6)
		(*data)->n_eat = (int)ft_atoi_long(argv[5]);
	(*data)->all_full = 0;
	(*data)->dead = 0;
	if (init_mutexes(data) != 0)
		return (1);
	return (0);
}

int	init_mutexes(t_data **data)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * (size_t)MUTEX_NUMBERS);
	if (mutex == NULL)
		return (1);
	while (i < MUTEX_NUMBERS)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	(*data)->mutex = mutex;
	return (0);
}

int	init_philo(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * (size_t)data->n_philos);
	if (fork == NULL)
		return (1);
	while (i < data->n_philos)
		if (pthread_mutex_init (&fork[i++], NULL))
			return (1);
	i = -1;
	while (++i < data->n_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].t_last_eat = data->basetime;
		(*philo)[i].meals_count = 0;
		(*philo)[i].left_fork = i;
		if (i - 1 < 0)
			(*philo)[i].right_fork = data->n_philos - 1;
		else
			(*philo)[i].right_fork = i - 1;
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
	}
	return (0);
}
