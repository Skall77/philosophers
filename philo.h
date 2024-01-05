/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudevar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:57:02 by aaudevar          #+#    #+#             */
/*   Updated: 2023/02/03 17:25:45 by aaudevar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	unsigned long	t_last_eat;
	int				meals_count;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	*fork;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_think;
	int				n_eat;
	unsigned long	basetime;
	int				all_full;
	int				dead;
	pthread_mutex_t	*mutex;
}			t_data;

typedef enum e_mutex
{
	LOGS,
	EAT,
	FULL,
	DEAD,
	MUTEX_NUMBERS
}	t_mutex;

//////// philo.c //////////////

int				check_arg(int argc, char **argv);
int				is_num(char *str);
int				special_cases(int argc, char **argv);
void			free_all(t_philo *philo, t_data *data);

//////// utils.c //////////////

int				message_error(char *str, int n);
long			ft_atoi_long(char *nptr);
int				max(int a, int b);
int				min(int a, int b);

//////// init.c //////////////

int				init_all(t_philo **philo, t_data **data, int argc, char **argv);
int				init_data(t_data **data, int argc, char **argv);
int				init_mutexes(t_data **data);
int				init_philo(t_philo **philo, t_data *data);

//////// time.c //////////////

unsigned long	get_time(void);
unsigned long	relative_time(unsigned long time);
void			smart_sleep(unsigned long m_seconds);

//////// threads.c //////////////

int				threads(t_philo *philo, t_data *data);
int				destroy_mutex(t_philo *philo, t_data *data, pthread_t *th,
					int ret);
int				check_if_done(t_philo *philo, t_data *data);
int				are_all_full(t_philo *philo, t_data *data);

//////// mutex.c //////////////

void			all_full(t_data *data);
void			all_dead(t_data *data);
void			print_logs(t_philo *philo, char *str);
int				is_dead(t_philo *philo);
int				is_full(t_philo *philo);

//////// routine.c //////////////

void			*routine(void *arg);
int				eat(t_philo *philo);
int				start_eat(t_philo *philo);
int				sleeping(t_philo *philo);

#endif