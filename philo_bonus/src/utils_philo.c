/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dannromm <dannromm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:41:50 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 11:10:21 by dannromm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_message(t_philo *philo, char *msg)
{
	sem_wait(philo->sem_write);
	if (!(philo->data->must_die))
		printf("%lld %d %s\n",
			timestamp(philo->start_time), philo->num + 1, msg);
	sem_post(philo->sem_write);
}

int32_t	check_died_time(t_philo *philo)
{
	if (get_time_ms() - philo->last_eat > philo->die_ms)
	{
		died(philo);
		sem_post(philo->sem_forks);
		return (1);
	}
	return (0);
}

void	died(t_philo *philo)
{
	sem_wait(philo->sem_write);
	if (!(philo->data->must_die))
		printf("%lld %d %s\n", timestamp(philo->start_time), philo->num + 1, DIED_MSG);
	philo->data->must_die = 1;
}

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (data->pids[i] && i < data->num)
	{
		kill(data->pids[i], SIGTERM);
		i++;
	}
	exit(1);
}

void	*death_checker(void *thread_data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)thread_data;
	while (1)
	{
		sem_wait(philo->sem_check);
		if (check_died_time(philo) || philo->data->must_die)
		{
			sem_wait(philo->sem_write);
			philo->data->must_die = 1;
			i = -1;
			while (++i < philo->data->num)
			{
				if (i != philo->num)
				{
					printf("[%d] here\n", philo->num);
					kill(philo->data->pids[i], SIGTERM);
				}
			}
		}
		sem_post(philo->sem_check);
		usleep(500);
	}
	exit(1);
}
