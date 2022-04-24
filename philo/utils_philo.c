/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:48:16 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 00:04:40 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_mutex);
	if (msg)
	{
		printf("%lld %d %s\n",
			timestamp(philo->start_time), philo->n + 1, msg);
		pthread_mutex_unlock(philo->write_mutex);
	}
	else
		printf("%lld %d %s\n",
			timestamp(philo->start_time), philo->n + 1, DIED_MSG);
}
