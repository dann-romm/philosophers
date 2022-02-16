/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:50 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/16 16:28:51 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_pdata *pdata, char *msg)
{
	pthread_mutex_lock(pdata->write_mutex);
	if (!(*(pdata->must_die)))
		printf("%lld %d %s\n",
			timestamp(pdata->start_time), pdata->num + 1, msg);
	pthread_mutex_unlock(pdata->write_mutex);
}

int	check_died_time(t_pdata *pdata)
{
	if (get_time_ms() - pdata->last_eat > pdata->die_ms)
	{
		died(pdata);
		pthread_mutex_unlock(&(pdata->left->mutex));
		pthread_mutex_unlock(&(pdata->right->mutex));
		return (1);
	}
	return (0);
}

void	died(t_pdata *pdata)
{
	pthread_mutex_lock(pdata->write_mutex);
	if (!(*(pdata->must_die)))
		printf("%lld %d %s\n", timestamp(pdata->start_time), pdata->num + 1, DIED_MSG);
	*(pdata->must_die) = 1;
	pthread_mutex_unlock(pdata->write_mutex);
}
