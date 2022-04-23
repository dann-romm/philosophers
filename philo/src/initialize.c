#include "philosophers.h"

int32_t	init_data(t_data *data, int32_t argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->num = ft_atoi(argv[1]);

	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->num);
	if (!data->forks)
		return (1);

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}

	memset(data->forks, 0, sizeof(t_fork) * data->num);
	memset(data->philos, 0, sizeof(t_philo) * data->num);


	if (pthread_mutex_init(&data->write_mutex, NULL)
		|| init_forks(data)
		|| (argc == 5 && init_philos(data, argv, -1))
		|| (argc == 6 && init_philos(data, argv, ft_atoi(argv[5]))))
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
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
		{
			free(data->philos);
			free(data->forks);
			return (1);
		}
	}
	return (0);
}

int32_t	init_philos(t_data *data, char **argv, int64_t eat_count)
{
	int32_t			i;
	const int64_t	die_ms = (int64_t)ft_atoi(argv[2]);
	const int64_t	eat_ms = (int64_t)ft_atoi(argv[3]);
	const int64_t	sleep_ms = (int64_t)ft_atoi(argv[4]);
	const int64_t	start_time = get_time_ms();

	pthread_t	id;

	i = -1;
	while (++i < data->num)
	{
		data->philos[i].n = i;
		data->philos[i].left = data->forks + i;
		data->philos[i].right = data->forks + (i + 1) % data->num;
		data->philos[i].die_ms = die_ms;
		data->philos[i].eat_ms = eat_ms;
		data->philos[i].sleep_ms = sleep_ms;
		data->philos[i].eat_count = eat_count;
		data->philos[i].write_mutex = &data->write_mutex;
		data->philos[i].last_eat = start_time;
		data->philos[i].start_time = start_time;
		if (pthread_mutex_init(&data->philos[i].last_eat_mutex, NULL))
			return (1);
		if (pthread_create(&id, NULL, philosopher, data->philos + i))
			return (1);
		pthread_detach(id);
	}
	return (0);
}
