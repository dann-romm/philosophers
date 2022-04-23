/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:40:30 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 00:45:39 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define DIED_MSG "died"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define TAKING_FORK_MSG "has taken a fork"

# define SEM_EATING_NAME "philo_sem_eating_000"
# define SEM_WRITE_NAME "philo_sem_write"
# define SEM_FORKS_NAME "philo_sem_forks"

// memset
# include <string.h>
// printf
# include <stdio.h>
// malloc free exit
# include <stdlib.h>
// write fork usleep
# include <unistd.h>
// kill
# include <signal.h>
// waitpid
# include <sys/wait.h>
// pthread_create pthread_detach, pthread_join
# include <pthread.h>
// gettimeofday
# include <sys/time.h>
// sem_open sem_close sem_pos sem_wait sem_unlink
# include <semaphore.h>
# include <stdint.h>

typedef struct s_philo
{
	int32_t		n;
	sem_t		*eating_sem;
	pid_t		pid;
	int64_t		last_eat;
	int32_t		eat_count;
}	t_philo;

typedef struct s_data
{
	int32_t		num;
	t_philo		*philos;

	pthread_t	thread_id;

	int64_t		eat_ms;
	int64_t		sleep_ms;
	int64_t		die_ms;
	int32_t		eat_count;
	int64_t		start_time;

	sem_t		*forks;
	sem_t		*write_sem;
}	t_data;

// typedef struct 
// {
// 	int32_t			num;
// 	t_data			*data;
// 	pthread_t		check_die;

// 	int64_t			die_ms;
// 	int64_t			eat_ms;
// 	int64_t			sleep_ms;
// 	int64_t			eat_count;

// 	int64_t			start_time;
// 	int64_t			last_eat;
	
// 	sem_t			*sem_forks;
// 	sem_t			*sem_write;
// 	sem_t			*sem_check;
// }			t_philo;

// typedef struct s_data
// {
// 	int32_t			num;
// 	int32_t			must_die;
// 	pid_t			*pids;
// 	t_philo			**philo;

// 	sem_t			*sem_forks;
// 	sem_t			*sem_write;
// 	sem_t			*sem_check;
// }				t_data;

// philosopher.c
void		*philosopher(t_philo *philo);

// initialize.c
int32_t		init_data(t_data *data, int32_t argc, char **argv);
int32_t		init_philos(t_data *data, char **argv, int64_t	eat_count);
int32_t		init_processes(t_data *data);

// utils_ft.c
int32_t		ft_atoi(const char *str);
char		*ft_strcpy(char *dest, char *src);

// utils_philo.c
void		print_message(t_philo *philo, char *msg);
int32_t		check_died_time(t_philo *philo);
void		died(t_philo *philo);
void		*death_checker(void *thread_data);
void		kill_all(t_data *data);

// time.c
int64_t		get_time_ms(void);
int64_t		timestamp(int64_t start_time);
void		sleep_ms(int64_t ms);

#endif
