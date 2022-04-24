/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:48:16 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 18:13:10 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	print_message(t_data *data, char *msg, int n)
{
	sem_wait(data->write_sem);
	if (msg)
	{
		printf("%lld %d %s\n",
			timestamp(data->start_time), n + 1, msg);
		sem_post(data->write_sem);
	}
	else
		printf("%lld %d %s\n",
			timestamp(data->start_time), n + 1, DIED_MSG);
}
