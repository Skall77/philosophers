/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:53:08 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:27:17 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
	{
		print_logs(philo, "is thinking");
		smart_sleep(philo->data->t_eat);
	}
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (eat(philo) != 0)
			break ;
		print_logs(philo, "is thinking");
		smart_sleep(philo->data->t_think);
	}
	return (NULL);
}

int	eat(t_philo *philo)
{
	if (start_eat(philo) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->mutex[EAT]);
	philo->t_last_eat = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->mutex[EAT]);
	if (is_full(philo))
	{
		sleeping(philo);
		return (1);
	}
	smart_sleep(philo->data->t_eat);
	sleeping(philo);
	return (0);
}

int	start_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[min(philo->left_fork, philo->right_fork)]);
	print_logs(philo, "has taken a fork");
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_unlock(&philo->fork[min(philo->left_fork,
				philo->right_fork)]);
		return (1);
	}
	pthread_mutex_lock(&philo->fork[max(philo->left_fork, philo->right_fork)]);
	print_logs(philo, "has taken a fork");
	print_logs(philo, "is eating");
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_logs(philo, "is sleeping");
	pthread_mutex_unlock(&philo->fork[max(philo->left_fork,
			philo->right_fork)]);
	pthread_mutex_unlock(&philo->fork[min(philo->left_fork,
			philo->right_fork)]);
	smart_sleep(philo->data->t_sleep);
	return (0);
}
