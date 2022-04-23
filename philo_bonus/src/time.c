/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dannromm <dannromm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:55 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 11:10:21 by dannromm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	sleep_ms(t_philo *philo, int64_t ms)
{
	int64_t	time_start;
	int64_t	time_current;

	time_start = get_time_ms();
	time_current = get_time_ms();
	while (time_current - time_start < ms && !(philo->data->must_die))
	{
		if (time_current - philo->last_eat > philo->die_ms)
			return (died(philo));
		usleep(100);
		time_current = get_time_ms();
	}
	if (time_current - philo->last_eat > philo->die_ms)
		return (died(philo));
}
