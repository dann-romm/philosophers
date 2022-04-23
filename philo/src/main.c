#include "philosophers.h"

int	destroy_mutexes(t_data *data)
{
	int32_t	i;

	if (pthread_mutex_destroy(&data->write_mutex))
		return (1);
	i = -1;
	while (++i < data->num)
	{
		if (pthread_mutex_destroy(&data->forks[i].mutex))
			return (1);
	}
	return (0);
}

int	is_philo_died(t_philo *philo) // print_message here
{
	// if (!philo->eat_count)
	// 	return (1);
	// else if (get_time_ms() - philo->last_eat > philo->die_ms)
	
	if (get_time_ms() - philo->last_eat > philo->die_ms)
	{
		print_message(philo, DIED_MSG);
		return (1);
	}
	else
		return (0);
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
			if (data->philos[i].eat_count)
				eat_stops = 0;
			if (is_philo_died(data->philos + i))
			{
				destroy_mutexes(data);
				return (1);
			}
		}
		if (eat_stops)
		{
			destroy_mutexes(data);
			return (0);
		}
		usleep(100);
	}
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;
	
	if (init_data(&data, argc, argv))
		return (1);
	return (run_philos_observer(&data));
}
