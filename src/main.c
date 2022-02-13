#include "philosophers.h"

int32_t	free_data(t_mdata *mdata, int32_t exit_code)
{
	int32_t	i;

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

int32_t	main(int32_t argc, char **argv)
{
	t_mdata	*mdata;

	mdata = (t_mdata *)malloc(sizeof(t_mdata));
	if (!mdata)
		return (1);
	init_mdata(mdata, argc, argv);
	init_forks(mdata);
	if (argc < 6)
		init_pdata(mdata, argv, -1);
	else
		init_pdata(mdata, argv, ft_atoi(argv[5]));

	init_threads(mdata);


	int32_t	i;

	i = -1;
	while (++i < mdata->num)
		pthread_join(mdata->threads[i], 0);
}
