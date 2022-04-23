#include "philosophers.h"

// TODO: if it is DIE_MSG, don't unlock write mutex
void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_mutex);
	if (msg)
	{
		printf("%lld %d %s\n",
			timestamp(philo->start_time), philo->n + 1, msg);
		pthread_mutex_unlock(philo->write_mutex);
	}
	else
		printf("%lld %d %s\n",
			timestamp(philo->start_time), philo->n + 1, DIED_MSG);
}
