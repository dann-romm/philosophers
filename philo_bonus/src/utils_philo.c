/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:50 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/17 16:03:15 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(t_pdata *pdata, char *msg)
{
	sem_wait(pdata->sem_write);
	if (!(pdata->mdata->must_die))
		printf("%lld %d %s\n",
			timestamp(pdata->start_time), pdata->num + 1, msg);
	sem_post(pdata->sem_write);
}

int32_t	check_died_time(t_pdata *pdata)
{
	if (get_time_ms() - pdata->last_eat > pdata->die_ms)
	{
		died(pdata);
		sem_post(pdata->sem_forks);
		return (1);
	}
	return (0);
}

void	died(t_pdata *pdata)
{
	sem_wait(pdata->sem_write);
	if (!(pdata->mdata->must_die))
		printf("%lld %d %s\n", timestamp(pdata->start_time), pdata->num + 1, DIED_MSG);
	pdata->mdata->must_die = 1;
}

void	kill_all(t_mdata *mdata)
{
	int	i;

	i = 0;
	while (mdata->pids[i] && i < mdata->num)
	{
		kill(mdata->pids[i], SIGTERM);
		i++;
	}
	exit(1);
}

void	*death_checker(void *thread_data)
{
	t_pdata	*pdata;
	int		i;

	pdata = (t_pdata *)thread_data;
	while (1)
	{
		sem_wait(pdata->sem_check);
		if (check_died_time(pdata) || pdata->mdata->must_die)
		{
			sem_wait(pdata->sem_write);
			pdata->mdata->must_die = 1;
			i = -1;
			while (++i < pdata->mdata->num)
			{
				if (i != pdata->num)
				{
					printf("[%d] here\n", pdata->num);
					kill(pdata->mdata->pids[i], SIGTERM);
				}
			}
		}
		sem_post(pdata->sem_check);
		usleep(500);
	}
	exit(1);
}
