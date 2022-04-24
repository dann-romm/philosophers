/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:10 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 18:15:48 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int32_t	init_sems(t_data *data)
{
	char	sem_name[21];
	int32_t	i;

	ft_strcpy(sem_name, SEM_EATING_NAME);
	i = -1;
	while (++i < data->num)
	{
		sem_name[17] = i / 100 + '0';
		sem_name[18] = i / 10 % 10 + '0';
		sem_name[19] = i % 10 + '0';
		data->philos[i].eat_count = 0;
		sem_unlink(sem_name);
		data->philos[i].eating_sem = sem_open(sem_name, O_CREAT, S_IRWXU, 0);
		if (data->philos[i].eating_sem == SEM_FAILED)
			return (1);
	}
	sem_unlink(SEM_FORKS_NAME);
	data->forks = sem_open(SEM_FORKS_NAME, O_CREAT, S_IRWXU, data->num);
	if (data->forks == SEM_FAILED)
		return (1);
	sem_unlink(SEM_WRITE_NAME);
	data->write_sem = sem_open(SEM_WRITE_NAME, O_CREAT, S_IRWXU, 1);
	if (data->write_sem == SEM_FAILED)
		return (1);
	return (0);
}

int32_t	init_data(t_data *data, int32_t argc, char **argv)
{
	data->num = ft_atoi(argv[1]);
	data->die_ms = (int64_t) ft_atoi(argv[2]);
	data->eat_ms = (int64_t) ft_atoi(argv[3]);
	data->sleep_ms = (int64_t) ft_atoi(argv[4]);
	data->eat_count = -1;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	if (data->num == 0 || data->num > 200 || data->eat_count == 0)
		return (1);
	data->start_time = get_time_ms();
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num);
	if (!data->philos)
		return (1);
	memset(data->philos, 0, sizeof(t_philo) * data->num);
	if (init_sems(data))
		return (1);
	return (0);
}
