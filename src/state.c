/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:57:43 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/16 11:01:44 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	eating(t_data *data, int i)
{
	use_fork(data, i);
	pthread_mutex_lock(&data->mutex_eat_or_alive);
	gettimeofday(&data->last_meal[i - 1], NULL);
	pthread_mutex_unlock(&data->mutex_eat_or_alive);
	message("is eating", i, data);
	usleep(data->eat * 1000);
	pthread_mutex_lock(&data->mutex_round_reach);
	if (data->round > 0)
		++data->finish[i - 1];
	pthread_mutex_unlock(&data->mutex_round_reach);
	put_down_fork(data, i);
}

static void	sleeping(t_data *data, int i)
{
	message("is sleeping", i, data);
	usleep(data->sleep * 1000);
}

static void	thinking(t_data *data, int i)
{
	if (i % 2)
		usleep(data->death / 4);
	message("is thinking", i, data);
}

void	algo_philo(t_data *data, int philo_nb)
{
	if (data->philo > 1)
	{
		eating(data, philo_nb);
		sleeping(data, philo_nb);
		thinking(data, philo_nb);
	}
}
