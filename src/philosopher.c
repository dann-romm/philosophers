#include "philosophers.h"


void	p_sleep(t_pdata *pdata)
{
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr(timestamp(pdata->start_time));
	write(1, " ", 1);
	ft_putnbr(pdata->num + 1);
	write(1, SLEEPING_MSG, SLEEPING_MSG_LEN);
	pthread_mutex_unlock(pdata->write_mutex);
	usleep(pdata->sleep_ms);
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr(timestamp(pdata->start_time));
	write(1, " ", 1);
	ft_putnbr(pdata->num + 1);
	write(1, THINKING_MSG, THINKING_MSG_LEN);
	pthread_mutex_unlock(pdata->write_mutex);
}

void	fork_msg(t_pdata *pdata)
{
	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr(timestamp(pdata->start_time));
	write(1, " ", 1);
	ft_putnbr(pdata->num + 1);
	write(1, TAKING_FORK_MSG, TAKING_FORK_MSG_LEN);
	pthread_mutex_unlock(pdata->write_mutex);
}

void	sleep_ms(int64_t ms)
{

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
	fork_msg(pdata);
	pthread_mutex_lock(&(max_fork->mutex));
	fork_msg(pdata);

	pthread_mutex_lock(pdata->write_mutex);
	ft_putnbr(timestamp(pdata->start_time));
	write(1, " ", 1);
	ft_putnbr(pdata->num + 1);
	write(1, EATING_MSG, EATING_MSG_LEN);
	pthread_mutex_unlock(pdata->write_mutex);
	usleep(pdata->eat_ms);

	pthread_mutex_unlock(&(max_fork->mutex));
	pthread_mutex_unlock(&(min_fork->mutex));
}

void	*philosopher(void *thread_data)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)thread_data;
	if (pdata->num % 2)
		usleep(pdata->sleep_ms / 2);
	while (*(pdata->must_die) == 0)
	{
		p_eat(pdata);
		p_sleep(pdata);
	}
	return (0);
}