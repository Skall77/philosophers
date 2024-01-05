/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:56:53 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:34:41 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (check_arg(argc, argv) != 0)
		return (1);
	if (special_cases(argc, argv))
		return (0);
	if (init_all(&philo, &data, argc, argv) != 0)
	{
		free_all(philo, data);
		return (1);
	}
	if (threads(philo, data) != 0)
	{
		free_all(philo, data);
		return (1);
	}
	free_all(philo, data);
	return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	check_arg(int argc, char **argv)
{
	if (argc < 5)
		return (message_error("Too few arguments\n", 1));
	if (argc > 6)
		return (message_error("Too many arguments\n", 1));
	while (argc > 1)
	{
		argc--;
		if (is_num(argv[argc]) != 1)
			return (message_error("Arguments need to be unsigned integers\n",
					1));
		if (ft_atoi_long(argv[argc]) > INT_MAX || ft_atoi_long(argv[argc]) < 0)
			return (message_error("Out of range arguments\n", 1));
	}
	return (0);
}

int	special_cases(int argc, char **argv)
{
	if (argc == 6 && ft_atoi_long(argv[5]) == 0)
		return (1);
	if (ft_atoi_long(argv[1]) == 0)
		return (1);
	return (0);
}

void	free_all(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free(data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}
