/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:26 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 17:26:53 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutexes(t_data *data)
{
	int32_t	i;

	i = -1;
	while (++i < data->num)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		if (pthread_mutex_destroy(&data->philos[i].check_die_mutex))
			return (1);
	}
	if (pthread_mutex_destroy(&data->write_mutex))
		return (1);
	return (0);
}

int	is_philo_died(t_philo *philo, int64_t die_ms)
{
	pthread_mutex_lock(&philo->check_die_mutex);
	if (get_time_ms() - philo->last_eat > die_ms)
	{
		pthread_mutex_unlock(&philo->check_die_mutex);
		print_message(philo, NULL);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->check_die_mutex);
		return (0);
	}
}

int	run_philos_observer(t_data *data)
{
	int32_t	i;
	int32_t	eat_stops;

	while (1)
	{
		i = -1;
		eat_stops = 1;
		while (++i < data->num)
		{
			if (data->eat_count == -1
				|| data->philos[i].eat_count < data->eat_count)
				eat_stops = 0;
			if (is_philo_died(data->philos + i, data->die_ms))
			{
				data->must_die = 1;
				sleep_ms(100);
				return (destroy_mutexes(data) + 1);
			}
		}
		if (eat_stops)
			return (destroy_mutexes(data));
		usleep(250);
	}
}

int	check_args(int argc, char **argv)
{
	int		i;
	char	*str;

	if (argc != 5 && argc != 6)
		return (1);
	i = 0;
	while (++i < argc)
	{
		str = argv[i];
		if (!*str)
			return (1);
		if (*str == '+')
			str++;
		while (*str >= '0' && *str <= '9')
			str++;
		if (*str)
			return (1);
	}
	return (0);
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
	{
		if (data.forks)
			free(data.forks);
		if (data.philos)
			free(data.philos);
		return (1);
	}
	if (init_forks(&data) || init_philos(&data, argv, (pthread_t) 0))
	{
		free(data.forks);
		free(data.philos);
		return (1);
	}
	return (run_philos_observer(&data));
}
