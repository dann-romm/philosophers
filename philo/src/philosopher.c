#include "philosophers.h"

void	p_sleep(t_philo *philo)
{
	print_message(philo, SLEEPING_MSG);
	sleep_ms(philo->sleep_ms);
}

void	take_forks(t_philo *philo)
{
	if (philo->left->n <= philo->right->n)
	{
		pthread_mutex_lock(&philo->left->mutex);
		print_message(philo, TAKING_FORK_MSG);
	}
	pthread_mutex_lock(&philo->right->mutex);
	print_message(philo, TAKING_FORK_MSG);
	if (philo->left->n >= philo->right->n)
	{
		pthread_mutex_lock(&philo->left->mutex);
		print_message(philo, TAKING_FORK_MSG);
	}
}

void	put_forks(t_philo *philo)
{
	if (philo->left->n >= philo->right->n)
		pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	if (philo->left->n <= philo->right->n)
		pthread_mutex_unlock(&philo->left->mutex);
}

void	p_eat(t_philo *philo, int first_iter)
{
	take_forks(philo);
	print_message(philo, EATING_MSG);
	sleep_ms(philo->eat_ms);
	pthread_mutex_lock(&philo->check_die_mutex);
	philo->eat_count++;
	philo->last_eat = get_time_ms() + first_iter * philo->sleep_ms;
	pthread_mutex_unlock(&philo->check_die_mutex);
	put_forks(philo);
}

void	*philosopher(void *thread_data)
{
	t_philo	*philo;

	philo = (t_philo *)thread_data;
	if (philo->n % 2)
		usleep((philo->eat_ms / 2) * 1000);
	p_eat(philo, 0);
	p_sleep(philo);
	print_message(philo, THINKING_MSG);
	while (1)
	{
		p_eat(philo, 1);
		p_sleep(philo);
		print_message(philo, THINKING_MSG);
	}
	return (0);
}
