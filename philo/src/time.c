/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:59 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 19:06:03 by doalbaco         ###   ########.fr       */
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

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

void	sleep_ms(int64_t ms)
{
	const int64_t	time_start = get_time_ms();
	int64_t			time_current;

	time_current = time_start;
	while (time_current - time_start < ms)
	{
		usleep(100);
		time_current = get_time_ms();
	}
}
