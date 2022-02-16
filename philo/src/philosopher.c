/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:43:24 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/14 17:43:25 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_sleep(t_pdata *pdata)
{
	if (!(*(pdata->must_die)))
	{
		print_message(pdata, SLEEPING_MSG);
		sleep_ms(pdata, pdata->sleep_ms);
		if (check_died_time(pdata))
			return ;
		print_message(pdata, THINKING_MSG);
	}
}

void	take_forks(t_pdata *pdata)
{
	if (pdata->left->num < pdata->right->num)
	{
		pthread_mutex_lock(&(pdata->left->mutex));
		print_message(pdata, TAKING_FORK_MSG);
		if (check_died_time(pdata))
			return ;
	}
	pthread_mutex_lock(&(pdata->right->mutex));
	if (check_died_time(pdata))
		return ;
	print_message(pdata, TAKING_FORK_MSG);
	if (pdata->left->num > pdata->right->num)
	{
		pthread_mutex_lock(&(pdata->left->mutex));
		if (check_died_time(pdata))
			return ;
		print_message(pdata, TAKING_FORK_MSG);
	}
}

void	put_forks(t_pdata *pdata)
{
	if (pdata->left->num > pdata->right->num)
		pthread_mutex_unlock(&(pdata->left->mutex));
	pthread_mutex_unlock(&(pdata->right->mutex));
	if (pdata->left->num < pdata->right->num)
		pthread_mutex_unlock(&(pdata->left->mutex));
}

void	p_eat(t_pdata *pdata)
{
	take_forks(pdata);
	print_message(pdata, EATING_MSG);
	pdata->last_eat = get_time_ms();
	sleep_ms(pdata, pdata->eat_ms);
	put_forks(pdata);
}

void	*philosopher(void *thread_data)
{
	t_pdata	*pdata;

	pdata = (t_pdata *)thread_data;
	if (pdata->num % 2)
		sleep_ms(pdata, pdata->sleep_ms / 2);
	while (*(pdata->must_die) == 0)
	{
		p_eat(pdata);
		p_sleep(pdata);
	}
	return (0);
}
