/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:26 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 18:13:42 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	kill_philos(t_data *data)
{
	pid_t	died_philo;
	int32_t	eating_done_count;
	int32_t	status;
	int32_t	i;

	status = 0;
	eating_done_count = 0;
	while (eating_done_count < data->num && !WEXITSTATUS(status))
	{
		eating_done_count++;
		died_philo = waitpid(-1, &status, 0);
		i = -1;
		while (++i < data->num)
		{
			if (data->philos[i].pid == died_philo)
				data->philos[i].is_dead = 1;
		}
	}
	i = -1;
	while (++i < data->num)
	{
		if (!data->philos[i].is_dead)
			kill(data->philos[i].pid, SIGKILL);
	}
}

static void	close_all_sems(t_data *data)
{
	int32_t	i;
	char	sem_name[21];

	ft_strcpy(sem_name, SEM_EATING_NAME);
	i = -1;
	while (++i < data->num)
	{
		sem_name[17] = i / 100 + '0';
		sem_name[18] = i / 10 % 10 + '0';
		sem_name[19] = i % 10 + '0';
		sem_close(data->philos[i].eating_sem);
		sem_unlink(sem_name);
	}
	sem_close(data->forks);
	sem_close(data->write_sem);
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_WRITE_NAME);
}

static int	run_philos(t_data *data)
{
	int32_t	i;

	i = -1;
	while (++i < data->num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			philosopher(data, i);
	}
	kill_philos(data);
	close_all_sems(data);
	return (0);
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
	{
		if (data.philos)
			free(data.philos);
		return (1);
	}
	return (run_philos(&data));
}
