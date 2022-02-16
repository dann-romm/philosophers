/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:53 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/14 17:43:19 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (exit_code);
}

int32_t	main(int32_t argc, char **argv)
{
	t_mdata	*mdata;
	int32_t	i;

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
	i = -1;
	while (++i < mdata->num)
		pthread_join(mdata->threads[i], 0);
}
