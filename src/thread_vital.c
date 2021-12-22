/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_vital.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:16:08 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/09 17:39:01 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	get_philo_nb_in_vital(t_data *data, int *philo_nb)
{
	pthread_mutex_lock(&data->mutex_nb);
	*philo_nb = data->temp;
	pthread_mutex_unlock(&data->mutex_nb);
}

static int	check_the_end_in_vital(t_data *data)
{
	pthread_mutex_lock(&data->mutex_is_finish);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->mutex_is_finish);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_is_finish);
	return (0);
}

static int	check_if_alive_in_vital(t_data *data, int philo_nb)
{
	long int	alive;

	pthread_mutex_lock(&data->mutex_eat_or_alive);
	alive = get_alive(philo_nb, data);
	if (alive >= data->death)
	{
		dead(philo_nb, data);
		pthread_mutex_unlock(&data->mutex_eat_or_alive);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_eat_or_alive);
	return (0);
}

static int	check_if_everybody_eat_in_vital(t_data *data, int philo_nb)
{
	pthread_mutex_lock(&data->mutex_round_reach);
	if (data->round > 0 && check_round(data))
	{
		round_reach(philo_nb, data);
		pthread_mutex_unlock(&data->mutex_round_reach);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_round_reach);
	return (0);
}

void	*check_vital(void *temp)
{
	t_data		*data;
	int			philo_nb;

	data = (t_data *) temp;
	get_philo_nb_in_vital(data, &philo_nb);
	while (1)
	{
		if (check_the_end_in_vital(data))
			break ;
		if (check_if_alive_in_vital(data, philo_nb))
			break ;
		if (check_if_everybody_eat_in_vital(data, philo_nb))
			break ;
		usleep(50);
	}
	return ((void *)0);
}
