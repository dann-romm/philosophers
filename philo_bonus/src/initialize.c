/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dannromm <dannromm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:15:14 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 11:10:21 by dannromm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int32_t	init_data(t_data *data, int32_t argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->num = ft_atoi(argv[1]);
	data->must_die = 0;
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->num);
	if (!data->pids)
		return (1);
	data->philo = (t_philo **)malloc(sizeof(t_philo *) * data->num);
	if (!data->philo)
		return (1);

	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_CHECK_NAME);
	data->sem_write = sem_open(SEM_WRITE_NAME, O_CREAT, S_IRWXU, 1);
	data->sem_forks = sem_open(SEM_FORKS_NAME, O_CREAT, S_IRWXU, data->num / 2);
	data->sem_check = sem_open(SEM_CHECK_NAME, O_CREAT, S_IRWXU, 1);
	return (0);
}

int32_t	init_philos(t_data *data, char **argv, int64_t	eat_count)
{
	int32_t	i;

	i = -1;
	while (++i < data->num)
	{
		data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (1);
		data->philo[i]->num = i;
		data->philo[i]->data = data;
	
		data->philo[i]->die_ms = (int64_t)ft_atoi(argv[2]);
		data->philo[i]->eat_ms = (int64_t)ft_atoi(argv[3]);
		data->philo[i]->sleep_ms = (int64_t)ft_atoi(argv[4]);
		data->philo[i]->eat_count = eat_count;
		
		data->philo[i]->sem_forks = data->sem_forks;
		data->philo[i]->sem_write = data->sem_write;
	}
	return (0);
}

int32_t	init_processes(t_data *data)
{
	int32_t	i;
	pid_t	pid;
	int64_t	start_time;

	i = -1;
	while (++i < data->num)
		data->pids[i] = 0;
	start_time = get_time_ms();
	i = -1;
	while (++i < data->num)
	{
		data->philo[i]->start_time = start_time;
		data->philo[i]->last_eat = start_time;
		pid = fork();
		if (pid < 0)
		{
			sem_wait(data->sem_write);
			i = 0;
			while (data->pids[i] && i < data->num)
			{
				kill(data->pids[i], SIGTERM);
				i++;
			}
			exit(1);
		}
		if (!pid)
			philosopher(data->philo[i]);
		else
			data->pids[i] = pid;
	}
	return (0);
}
