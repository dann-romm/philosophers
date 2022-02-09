#include "philosophers.h"

void	*thread_func(void *thread_data)
{
	printf("ok1\n");
	pthread_exit(0);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
void	parsing(t_mdata *mdata, int argc, char **argv)
{
	
}

int	main(int argc, char **argv)
{

}
