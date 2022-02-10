#include "philosophers.h"

void	p_sleep(t_pdata *pdata)
{
	// usleep();
}

void	*philosopher(void *pdata)
{
	printf("ok1\n");
	pthread_exit(0);
}