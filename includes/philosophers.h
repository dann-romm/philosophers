#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <pthread.h>

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

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
	pthread_t	*threads; // array with thread's id
	int			count; // number of forks / number of philosophers
	int			t_die; // time to die
	int			t_eat; // time to eat
	int			t_sleep; // time to sleep
	int			eat_count; // сколько раз философы должны покушать
}				t_mdata;

#endif
