/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:40:30 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/16 20:05:25 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define DIED_MSG "died"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define TAKING_FORK_MSG "has taken a fork"

# define SEM_WRITE_NAME "philo_sem_write"
# define SEM_FORKS_NAME "philo_sem_forks"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdint.h>

// memset, printf, malloc, free, write
// fork, kill, exit, waitpid
// pthread_create, pthread_detach, pthread_join,
// usleep, gettimeofday
// sem_open, sem_close, sem_post, sem_wait, sem_unlink

typedef struct s_pdata
{
	int32_t			num;
	int32_t			*must_die;

	int64_t			die_ms;
	int64_t			eat_ms;
	int64_t			sleep_ms;
	int64_t			eat_count;

	int64_t			start_time;
	int64_t			last_eat;
	
	sem_t			*sem_forks;
	sem_t			*sem_write;
}			t_pdata;

typedef struct s_mdata
{
	int32_t			num;
	int32_t			must_die;
	pid_t			*pids;
	t_pdata			**pdata;

	pthread_t		check_die;

	sem_t			*sem_forks;
	sem_t			*sem_write;
}				t_mdata;

// philosopher.c
void		*philosopher(t_pdata *pdata);

// initialize.c
int32_t		init_mdata(t_mdata *mdata, int32_t argc, char **argv);
int32_t		init_pdata(t_mdata *mdata, char **argv, int64_t	eat_count);
int32_t		init_processes(t_mdata *mdata);

// utils_ft.c
int32_t		ft_atoi(const char *str);
void		ft_putnbr(int64_t n);

// utils_philo.c
void		print_message(t_pdata *pdata, char *msg);
int32_t		check_died_time(t_pdata *pdata);
void		died(t_pdata *pdata);

// time.c
int64_t		get_time_ms(void);
int64_t		timestamp(int64_t start_time);
void		sleep_ms(t_pdata *pdata, int64_t ms);

#endif
