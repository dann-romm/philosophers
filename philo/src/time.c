/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:55 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/14 17:41:59 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int64_t	timestamp(int64_t start_time)
{
	struct timeval	time;

	if (gettimeofday(&time, 0))
		return (-1);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

void	sleep_ms(t_pdata *pdata, int64_t ms)
{
	int64_t	time_start;
	int64_t	time_current;

	time_start = get_time_ms();
	time_current = get_time_ms();
	while (time_current - time_start < ms && !(*(pdata->must_die)))
	{
		if (time_current - pdata->last_eat > pdata->die_ms)
			return (died(pdata));
		usleep(80);
		time_current = get_time_ms();
	}
	if (time_current - pdata->last_eat > pdata->die_ms)
		return (died(pdata));
}
