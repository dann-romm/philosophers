/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:10 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 00:08:32 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int32_t	init_data(t_data *data, int32_t argc, char **argv)
{
	data->philos = NULL;
	data->forks = NULL;
	data->num = ft_atoi(argv[1]);
	data->eat_count = -1;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	if (data->num == 0 || data->num > 200 || data->eat_count == 0)
		return (1);
	data->die_ms = (int64_t) ft_atoi(argv[2]);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->num);
	if (!data->forks)
		return (1);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num);
	if (!data->philos)
		return (1);
	memset(data->forks, 0, sizeof(t_fork) * data->num);
	memset(data->philos, 0, sizeof(t_philo) * data->num);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	data->must_die = 0;
	return (0);
}

int32_t	init_forks(t_data *data)
{
	int32_t	i;

	i = -1;
	while (++i < data->num)
	{
		data->forks[i].n = i;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			return (1);
	}
	return (0);
}

int32_t	init_philos(t_data *data, char **argv, pthread_t id)
{
	int32_t			i;
	const int64_t	eat_ms = (int64_t)ft_atoi(argv[3]);
	const int64_t	sleep_ms = (int64_t)ft_atoi(argv[4]);
	const int64_t	start_time = get_time_ms();

	i = -1;
	while (++i < data->num)
	{
		data->philos[i].n = i;
		data->philos[i].left = data->forks + i;
		data->philos[i].right = data->forks + (i + 1) % data->num;
		data->philos[i].eat_ms = eat_ms;
		data->philos[i].sleep_ms = sleep_ms;
		data->philos[i].eat_count = 0;
		data->philos[i].write_mutex = &data->write_mutex;
		data->philos[i].last_eat = start_time;
		data->philos[i].start_time = start_time;
		data->philos[i].must_die = &data->must_die;
		if (pthread_mutex_init(&data->philos[i].check_die_mutex, NULL))
			return (1);
		if (pthread_create(&id, NULL, philosopher, data->philos + i))
			return (1);
		pthread_detach(id);
	}
	return (0);
}
