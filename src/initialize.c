/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:15:14 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/10 16:59:07 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mdata(t_mdata *mdata, int argc, char **argv) // TODO: init write_mutex
{
	if (argc != 5 && argc != 6)
		return (1);
	mdata->num = ft_atoi(argv[1]);
	mdata->t_die = ft_atoi(argv[2]);
	mdata->t_eat = ft_atoi(argv[3]);
	mdata->t_sleep = ft_atoi(argv[4]);
	mdata->eat_count = -1;
	if (argc == 6)
		mdata->eat_count = ft_atoi(argv[5]);
	mdata->threads = (pthread_t *)malloc(sizeof(pthread_t) * mdata->num);
	if (!mdata->threads)
		return (1);
	mdata->forks = (t_fork **)malloc(sizeof(t_fork *) * mdata->num);
	if (!mdata->forks)
		return (1);
	mdata->pdata = (t_pdata **)malloc(sizeof(t_pdata *) * mdata->num);
	if (!mdata->pdata)
		return (1);
	pthread_mutex_init(&(mdata->write_mutex), 0); // TODO: save initialize
	return (0);
}

int	init_forks(t_mdata *mdata)
{
	int	i;

	i = -1;
	while (++i < mdata->num)
	{
		mdata->forks[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!mdata->forks[i])
			return (1);
		mdata->forks[i]->num = i;
		pthread_mutex_init(&(mdata->forks[i]->mutex), 0); // TODO: save initialize
	}
	return (0);
}

int	init_pdata(t_mdata *mdata)
{
	int	i;

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
		mdata->pdata[i]->must_die = 0;
	}
	return (0);
}

int	init_threads(t_mdata *mdata)
{
	int	i;

	i = -1;
	while (++i < mdata->num)
		mdata->threads[i] = 0;
	i = -1;
	while (++i < mdata->num)
	{
		if (pthread_create(&(mdata->threads[i]), 0,
				philosopher, mdata->pdata[i]))
		{
			printf("поток не открылся, надо закрыть все предыдущие хз\n"); // TODO: remove
			pthread_mutex_lock(&(mdata->write_mutex));
			i = -1;
			while (++i && mdata->threads[i])
			{
				mdata->pdata[i]->must_die = 1;
				pthread_detach(mdata->threads[i]);
			}
			return (1);
		}
		printf("thread %i created\n", i);
	}
	return (0);
}
