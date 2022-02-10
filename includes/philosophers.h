#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>

// memset, printf, malloc, free, write,
// usleep, gettimeofday
//
// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy
// pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				num;
}					t_fork;

typedef struct s_pdata
{
	int		num;
	t_fork	*left;
	t_fork	*right;
	int		must_die;
}			t_pdata;

typedef struct s_mdata
{
	pthread_t		*threads;
	t_pdata			**pdata;
	t_fork			**forks;
	int				num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_count;
	pthread_mutex_t	write_mutex;
}				t_mdata;

// philosopher.c
void	*philosopher(void *thread_data);

// initialize.c
int		init_mdata(t_mdata *mdata, int argc, char **argv);
int		init_forks(t_mdata *mdata);
int		init_pdata(t_mdata *mdata);
int		init_threads(t_mdata *mdata);

// utils_ft.c
int		ft_atoi(const char *str);

#endif
