#include "philosophers.h"

void	p_sleep(t_pdata *pdata)
{
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr_u(pdata->num + 1);
	write(1, " is sleeping\n", 13);
	pthread_mutex_unlock(pdata->write_mutex);
	usleep(pdata->t_sleep * 1000);
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr_u(pdata->num + 1);
	write(1, " is thinking\n", 13);
	pthread_mutex_unlock(pdata->write_mutex);
}

void	fork_msg(int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	ft_putnbr_u(num + 1);
	write(1, " has taken a fork\n", 18);
	pthread_mutex_unlock(mutex);
}

void	p_eat(t_pdata *pdata)
{
	t_fork	*min_fork;
	t_fork	*max_fork;

	min_fork = pdata->left;
	max_fork = pdata->right;
	if (pdata->left->num > pdata->right->num)
	{
		min_fork = pdata->right;
		max_fork = pdata->left;
	}
	pthread_mutex_lock(&(min_fork->mutex));
	fork_msg(pdata->num, pdata->write_mutex);
	pthread_mutex_lock(&(max_fork->mutex));
	fork_msg(pdata->num, pdata->write_mutex);
	
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr_u(pdata->num + 1);
	write(1, " is eating\n", 11);
	pthread_mutex_unlock(pdata->write_mutex);
	usleep(pdata->t_eat * 1000);

	pthread_mutex_unlock(&(max_fork->mutex));
	pthread_mutex_unlock(&(min_fork->mutex));
}

void	*philosopher(void *thread_data)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)thread_data;
	while (1)
	{
		p_eat(pdata);
		p_sleep(pdata);
	}
	return (0);
}