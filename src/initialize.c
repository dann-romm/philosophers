/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:15:14 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/14 01:46:34 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int32_t	init_mdata(t_mdata *mdata, int32_t argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	mdata->num = ft_atoi(argv[1]);
	mdata->must_die = 0;
	mdata->threads = (pthread_t *)malloc(sizeof(pthread_t) * mdata->num);
	if (!mdata->threads)
		return (1);
	mdata->forks = (t_fork **)malloc(sizeof(t_fork *) * mdata->num);
	if (!mdata->forks)
		return (1);
	mdata->pdata = (t_pdata **)malloc(sizeof(t_pdata *) * mdata->num);
	if (!mdata->pdata)
		return (1);
	if (pthread_mutex_init(&(mdata->write_mutex), 0))
		return (1);
	return (0);
}

int32_t	init_forks(t_mdata *mdata)
{
	int32_t	i;

	i = -1;
	while (++i < mdata->num)
	{
		mdata->forks[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!mdata->forks[i])
			return (1);
		mdata->forks[i]->num = i;
		if (pthread_mutex_init(&(mdata->forks[i]->mutex), 0))
			return (1);
	}
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
		mdata->pdata[i]->left
			= mdata->forks[(i + mdata->num - 1) % mdata->num];
		mdata->pdata[i]->right = mdata->forks[i];
		mdata->pdata[i]->must_die = &(mdata->must_die);
		mdata->pdata[i]->die_ms = (int64_t)ft_atoi(argv[2]);
		mdata->pdata[i]->eat_ms = (int64_t)ft_atoi(argv[3]);
		mdata->pdata[i]->sleep_ms = (int64_t)ft_atoi(argv[4]);
		mdata->pdata[i]->eat_count = eat_count;
		mdata->pdata[i]->write_mutex = &(mdata->write_mutex);
	}
	return (0);
}

int32_t	init_threads(t_mdata *mdata) // прикрутить время
{
	int32_t	i;
	int64_t	start_time;

	i = -1;
	while (++i < mdata->num)
		mdata->threads[i] = 0;
	start_time = get_time_ms();
	i = -1;
	while (++i < mdata->num)
	{
		mdata->pdata[i]->start_time = start_time;
		mdata->pdata[i]->last_eat = start_time;
		if (pthread_create(&(mdata->threads[i]), 0,
				philosopher, mdata->pdata[i]))
		{
			pthread_mutex_lock(&(mdata->write_mutex));
			printf("поток не открылся, надо закрыть все предыдущие хз\n"); // TODO: remove
			mdata->must_die = 1;
			i = 0;
			while (i && mdata->threads[i])
				pthread_detach(mdata->threads[i++]);
			return (1);
		}
	}
	return (0);
}
