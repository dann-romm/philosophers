/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dannromm <dannromm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:43:24 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/23 11:10:21 by dannromm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	p_sleep(t_philo *philo)
{
	if (!(philo->data->must_die))
	{
		print_message(philo, SLEEPING_MSG);
		sleep_ms(philo, philo->sleep_ms);
		if (check_died_time(philo))
			return ;
		print_message(philo, THINKING_MSG);
	}
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	print_message(philo, TAKING_FORK_MSG);
	print_message(philo, TAKING_FORK_MSG);
	if (check_died_time(philo))
		return ;
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->sem_forks);
}

void	p_eat(t_philo *philo)
{
	take_forks(philo);
	print_message(philo, EATING_MSG);
	philo->last_eat = get_time_ms();
	sleep_ms(philo, philo->eat_ms);
	put_forks(philo);
}

void	*philosopher(t_philo *philo)
{
	pthread_create(&(philo->check_die), 0, death_checker, philo);
	if (philo->num % 2)
		sleep_ms(philo, philo->sleep_ms / 2);
	while (philo->data->must_die == 0)
	{
		p_eat(philo);
		p_sleep(philo);
	}
	exit(0);
}
