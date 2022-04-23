/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:47:26 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 01:00:26 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philosopher(t_data *data, int n)
{
	return (0);
}

int	run_observer(t_data *data)
{
	return (0);
}

int	kill_philos()
{
	return (0);
}

int	close_all_sems()
{
	return (0);
}

int	run_philos(t_data *data)
{
	int32_t	i;
	pid_t	obsever;

	i = -1;
	while (++i < data->num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			exit(philosopher(data, i));
	}
	obsever = 0;
	if (data->eat_count == -1)
	{
		obsever = fork();
		if (obsever == 0)
			exit(run_observer(data));
	}
	kill_philos();
	close_all_sems();
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
		if (data.philos)
			free(data.philos);
		return (1);
	}
	return (run_philos(&data));
}
