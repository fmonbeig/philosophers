/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:11:46 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/09 15:27:10 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->mutex_nb);
	pthread_mutex_destroy(&data->mutex_message);
	pthread_mutex_destroy(&data->mutex_eat_or_alive);
	pthread_mutex_destroy(&data->mutex_is_finish);
	pthread_mutex_destroy(&data->mutex_round_reach);
}

void	free_malloc(t_data *data)
{
	if (data->fork)
		free(data->fork);
	if (data->finish)
		free(data->finish);
	if (data->last_meal)
		free(data->last_meal);
	if (data->phil)
		free(data->phil);
}

void	close_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo)
		pthread_join(data->phil[i], NULL);
}
