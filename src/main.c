#include "philosophers.h"

int	free_data(t_mdata *mdata, int exit_code)
{
	int	i;

	if (mdata)
	{
		if (mdata->threads)
			free(mdata->threads);
		if (mdata->pdata)
		{
			i = 0;
			while (i < mdata->num && mdata->pdata[i])
				free(mdata->pdata[i++]);
			free(mdata->pdata);
		}
		if (mdata->forks)
		{
			i = 0;
			while (i < mdata->num && mdata->forks[i])
				free(mdata->forks[i++]);
			free(mdata->forks);
		}
		free(mdata);
	}
	if (exit_code)
		printf("error exit\n");
	else
		printf("success exit\n");
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_mdata	*mdata;

	mdata = (t_mdata *)malloc(sizeof(t_mdata));
	if (!mdata)
		return (1);
	init_mdata(mdata, argc, argv);
	init_forks(mdata);
	init_pdata(mdata);
	init_threads(mdata);

	int	i;

	i = -1;
	while (++i < mdata->num)
		pthread_join(mdata->threads[i], 0);
}
