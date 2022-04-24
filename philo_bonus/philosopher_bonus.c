/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:57 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 18:26:39 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*philosopher_observer(void *thread_data)
{
	t_data	*data;

	data = (t_data *) thread_data;
	while (42)
	{
		if (timestamp(data->philos[data->num].last_eat) >= data->die_ms)
		{
			print_message(data, NULL, data->num);
			exit(1);
		}
		usleep(500);
	}
}

int	philosopher(t_data *data, int n)
{
	data->num = n;
	data->philos[n].last_eat = get_time_ms();
	pthread_create(&data->thread_id, NULL, philosopher_observer, data);
	pthread_detach(data->thread_id);
	while (data->eat_count)
	{
		sem_wait(data->forks);
		print_message(data, TAKING_FORK_MSG, n);
		sem_wait(data->forks);
		print_message(data, TAKING_FORK_MSG, n);
		print_message(data, EATING_MSG, n);
		if (data->eat_count != -1)
			data->eat_count--;
		sleep_ms(data->eat_ms);
		data->philos[n].last_eat = get_time_ms();
		sem_post(data->forks);
		sem_post(data->forks);
		print_message(data, SLEEPING_MSG, n);
		sleep_ms(data->sleep_ms);
		print_message(data, THINKING_MSG, n);
	}
	exit(0);
}
