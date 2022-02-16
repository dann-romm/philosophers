/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:15:14 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/16 20:07:15 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int32_t	init_mdata(t_mdata *mdata, int32_t argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	mdata->num = ft_atoi(argv[1]);
	mdata->must_die = 0;
	mdata->pids = (pid_t *)malloc(sizeof(pid_t) * mdata->num);
	if (!mdata->pids)
		return (1);
	mdata->pdata = (t_pdata **)malloc(sizeof(t_pdata *) * mdata->num);
	if (!mdata->pdata)
		return (1);

	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_FORKS_NAME);
	mdata->sem_write = sem_open(SEM_WRITE_NAME, O_CREAT, S_IRWXU, 1);
	mdata->sem_forks = sem_open(SEM_FORKS_NAME, O_CREAT, S_IRWXU, mdata->num / 2);
	return (0);
}

int32_t	init_pdata(t_mdata *mdata, char **argv, int64_t	eat_count)
{
	int32_t	i;

	i = -1;
	while (++i < mdata->num)
	{
		mdata->pdata[i] = (t_pdata *)malloc(sizeof(t_pdata));
		if (!mdata->pdata[i])
			return (1);
		mdata->pdata[i]->num = i;
		mdata->pdata[i]->must_die = &(mdata->must_die);
	
		mdata->pdata[i]->die_ms = (int64_t)ft_atoi(argv[2]);
		mdata->pdata[i]->eat_ms = (int64_t)ft_atoi(argv[3]);
		mdata->pdata[i]->sleep_ms = (int64_t)ft_atoi(argv[4]);
		mdata->pdata[i]->eat_count = eat_count;
		
		mdata->pdata[i]->sem_forks = mdata->sem_forks;
		mdata->pdata[i]->sem_write = mdata->sem_write;
	}
	return (0);
}

int32_t	init_processes(t_mdata *mdata)
{
	int32_t	i;
	pid_t	pid;
	int64_t	start_time;

	i = -1;
	while (++i < mdata->num)
		mdata->pids[i] = 0;
	start_time = get_time_ms();
	i = -1;
	while (++i < mdata->num)
	{
		mdata->pdata[i]->start_time = start_time;
		mdata->pdata[i]->last_eat = start_time;
		pid = fork();
		if (pid < 0)
		{
			sem_wait(mdata->sem_write);
			i = 0;
			while (mdata->pids[i] && i < mdata->num)
			{
				kill(mdata->pids[i], SIGTERM);
				i++;
			}
			exit(1);
		}
		if (!pid)
			philosopher(mdata->pdata[i]);
		else
			mdata->pids[i] = pid;
	}
	return (0);
}
