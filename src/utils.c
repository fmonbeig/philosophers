/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:59:46 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/09 15:32:29 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_round(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo)
	{
		if (data->finish[i] < data->round)
			return (0);
	}
	return (1);
}

long int	get_alive(int philo_nb, t_data *data)
{
	struct timeval		now;
	long int			alive;

	gettimeofday(&now, NULL);
	alive = ((now.tv_sec * 1000000 + now.tv_usec) / 1000)
		- ((data->last_meal[philo_nb - 1].tv_sec * 1000000
				+ data->last_meal[philo_nb - 1].tv_usec) / 1000);
	return (alive);
}

void	dead(int philo_nb, t_data *data)
{
	message("died", philo_nb, data);
	pthread_mutex_lock(&data->mutex_is_finish);
	data->end = 1;
	pthread_mutex_unlock(&data->mutex_is_finish);
}

void	round_reach(int philo_nb, t_data *data)
{
	message("say : all philosophers have eat", philo_nb, data);
	pthread_mutex_lock(&data->mutex_is_finish);
	data->end = 1;
	pthread_mutex_unlock(&data->mutex_is_finish);
}
