#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define EATING_MSG " is eating\n"
# define EATING_MSG_LEN 11
# define SLEEPING_MSG " is sleeping\n"
# define SLEEPING_MSG_LEN 13
# define THINKING_MSG " is thinking\n"
# define THINKING_MSG_LEN 13
# define TAKING_FORK_MSG " has taken a fork\n"
# define TAKING_FORK_MSG_LEN 18


# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>

// memset, printf, malloc, free, write,
// usleep, gettimeofday
//
// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy
// pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int32_t			num;
}					t_fork;

typedef struct s_pdata
{
	int32_t			num;
	t_fork			*left;
	t_fork			*right;
	int32_t			*must_die;

	int64_t			die_ms;
	int64_t			eat_ms;
	int64_t			sleep_ms;
	int64_t			eat_count;

	int64_t			start_time;
	int64_t			last_eat;

	pthread_mutex_t	*write_mutex;
}			t_pdata;

typedef struct s_mdata
{
	int32_t			num;
	pthread_t		*threads;
	t_pdata			**pdata;
	t_fork			**forks;
	int32_t			must_die;
	pthread_mutex_t	write_mutex;
}				t_mdata;

// philosopher.c
void		*philosopher(void *thread_data);

// initialize.c
int32_t		init_mdata(t_mdata *mdata, int32_t argc, char **argv);
int32_t		init_forks(t_mdata *mdata);
int32_t		init_pdata(t_mdata *mdata, char **argv, int64_t	eat_count);
int32_t		init_threads(t_mdata *mdata);

// utils_ft.c
int32_t		ft_atoi(const char *str);
void		ft_putnbr(int64_t n);

// utils_philo.c

// time.c
int64_t		get_time_ms(void);
int64_t		timestamp(int64_t start_time);

#endif
