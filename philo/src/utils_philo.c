#include "philosophers.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_mutex);
	printf("%lld %d %s\n", timestamp(philo->start_time), philo->n + 1, msg);
	pthread_mutex_unlock(philo->write_mutex);
}

// int	check_died_time(t_philo *philo)
// {
// 	if (get_time_ms() - philo->last_eat > philo->die_ms)
// 	{
// 		died(philo);
// 		pthread_mutex_unlock(&(philo->left->mutex));
// 		pthread_mutex_unlock(&(philo->right->mutex));
// 		return (1);
// 	}
// 	return (0);
// }

// void	died(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->write_mutex);
// 	if (!(*(philo->must_die)))
// 		printf("%lld %d %s\n", timestamp(philo->start_time), philo->num + 1, DIED_MSG);
// 	*(philo->must_die) = 1;
// 	pthread_mutex_unlock(philo->write_mutex);
// }
