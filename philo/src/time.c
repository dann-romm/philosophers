#include "philosophers.h"

int64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int64_t	timestamp(int64_t start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, 0))
		return (-1);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

void	sleep_ms(t_philo *philo, int64_t ms)
{
	int64_t	time_start;
	int64_t	time_current;

	(void) philo;
	time_start = get_time_ms();
	time_current = get_time_ms();
	while (time_current - time_start < ms)
	{
		usleep(100);
		time_current = get_time_ms();
	}
}
