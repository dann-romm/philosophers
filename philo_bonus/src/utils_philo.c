/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:50 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/16 20:04:29 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(t_pdata *pdata, char *msg)
{
	sem_wait(pdata->sem_write);
	if (!(*(pdata->must_die)))
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
	if (!(*(pdata->must_die)))
		printf("%lld %d %s\n", timestamp(pdata->start_time), pdata->num + 1, DIED_MSG);
	*(pdata->must_die) = 1;
	sem_post(pdata->sem_write);
}
