/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dannromm <dannromm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:53 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 11:10:21 by dannromm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int32_t	free_data(t_data *data, int32_t exit_code)
{
	int32_t	i;

	if (data)
	{
		if (data->pids)
			free(data->pids);
		if (data->philo)
		{
			i = 0;
			while (i < data->num && data->philo[i])
				free(data->philo[i++]);
			free(data->philo);
		}
		if (data->pids)
			free(data->pids);
		free(data);
	}
	return (exit_code);
}

int32_t	main(int32_t argc, char **argv)
{
	t_data	*data;
	int32_t	i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, argc, argv);
	if (argc < 6)
		init_philos(data, argv, -1);
	else
		init_philos(data, argv, ft_atoi(argv[5]));
	init_processes(data);
	waitpid(-1, 0, 0);
	kill_all(data);
	exit(0);
}
