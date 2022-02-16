#include "philosophers_bonus.h"

void	death_checker(void *thread_data)
{
	t_mdata	*mdata;
	int32_t	i;


	mdata = (t_mdata *)thread_data;
	// while (1)
	// {
	// 	i = -1;
	// 	while (++i < mdata->num)
	// 	{
	// 		if ()
	// 	}
	// }
}

void	init_death_checker(t_mdata *mdata)
{
	pthread_create(&(mdata->check_die), 0, death_checker, mdata);
}
