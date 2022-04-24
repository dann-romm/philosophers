/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:40:30 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 18:15:30 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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
	sem_t		*eating_sem;
	pid_t		pid;
	int64_t		last_eat;
	int32_t		eat_count;
	int32_t		is_dead;
}	t_philo;

typedef struct s_data
{
	int32_t		num;
	t_philo		*philos;

	pthread_t	thread_id;

	int64_t		die_ms;
	int64_t		eat_ms;
	int64_t		sleep_ms;
	int32_t		eat_count;
	int64_t		start_time;

	sem_t		*forks;
	sem_t		*write_sem;
}	t_data;

// philosopher.c
int			philosopher(t_data *data, int n);

// initialize.c
int32_t		init_data(t_data *data, int32_t argc, char **argv);

// utils_ft.c
int32_t		ft_atoi(const char *str);
char		*ft_strcpy(char *dest, char *src);

// utils_philo.c
void		print_message(t_data *data, char *msg, int n);
int			check_args(int argc, char **argv);

// time.c
int64_t		get_time_ms(void);
int64_t		timestamp(int64_t start_time);
void		sleep_ms(int64_t ms);

#endif
