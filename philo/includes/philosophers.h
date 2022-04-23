/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:40:30 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 18:28:37 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define DIED_MSG "died"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define TAKING_FORK_MSG "has taken a fork"

// maximum number of philosophers (threads)
# define PHILO_MAX 200

// memset
# include <string.h>
// printf
# include <stdio.h>
// malloc free
# include <stdlib.h>
// write usleep
# include <unistd.h>
// gettimeofday
# include <sys/time.h>
// pthread_create pthread_detach, pthread_join pthread_mutex_init
// pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock
# include <pthread.h>
# include <stdint.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	mutex;
	int32_t	n;
}	t_fork;

typedef struct s_philo
{
	int32_t		n;
	t_fork		*left;
	t_fork		*right;

	int64_t		eat_ms;
	int64_t		sleep_ms;
	int64_t		eat_count;

	int64_t		start_time;
	int64_t		last_eat;

	t_mutex		*write_mutex;
	t_mutex		check_die_mutex;
}	t_philo;

typedef struct s_data
{
	int32_t		num;
	int32_t		eat_count;
	int64_t		die_ms;
	t_philo		*philos;
	t_fork		*forks;
	t_mutex		write_mutex;
}	t_data;

// philosopher.c
void		*philosopher(void *thread_data);

// initialize.c
int32_t		init_data(t_data *data, int32_t argc, char **argv);
int32_t		init_forks(t_data *data);
int32_t		init_philos(t_data *data, char **argv, pthread_t id);

// utils_ft.c
int32_t		ft_atoi(const char *str);

// utils_philo.c
void		print_message(t_philo *philo, char *msg);
// int			check_died_time(t_philo *philo);
// void		died(t_philo *philo);

// time.c
int64_t		get_time_ms(void);
int64_t		timestamp(int64_t start_time);
void		sleep_ms(int64_t ms);

#endif
