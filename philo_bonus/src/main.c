/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:53 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/17 15:56:54 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int32_t	free_data(t_mdata *mdata, int32_t exit_code)
{
	int32_t	i;

	if (mdata)
	{
		if (mdata->pids)
			free(mdata->pids);
		if (mdata->pdata)
		{
			i = 0;
			while (i < mdata->num && mdata->pdata[i])
				free(mdata->pdata[i++]);
			free(mdata->pdata);
		}
		if (mdata->pids)
			free(mdata->pids);
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
	if (argc < 6)
		init_pdata(mdata, argv, -1);
	else
		init_pdata(mdata, argv, ft_atoi(argv[5]));
	init_processes(mdata);
	waitpid(-1, 0, 0);
	kill_all(mdata);
	exit(0);
}
