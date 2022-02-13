#include "philosophers.h"

int64_t	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0))
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int64_t	timestamp(int64_t start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, 0))
		return (-1);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}
