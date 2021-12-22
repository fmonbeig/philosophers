/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:27:47 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/13 17:52:32 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	get_philo_nb(t_data *data, int *philo_nb)
{
	pthread_mutex_lock(&data->mutex_nb);
	*philo_nb = ++data->temp;
	pthread_mutex_unlock(&data->mutex_nb);
}

static void	*failed_to_create_vital_thread(t_data *data)
{
	ft_putstr_fd("ERROR: failed to create a thread", 2);
	pthread_mutex_lock(&data->mutex_is_finish);
	data->end = 1;
	pthread_mutex_unlock(&data->mutex_is_finish);
	return ((void *) 1);
}

void	*philosophers(void *temp)
{
	int			philo_nb;
	t_data		*data;
	pthread_t	check;

	data = (t_data *)temp;
	get_philo_nb(data, &philo_nb);
	if (pthread_create(&check, NULL, &check_vital, data) != 0)
		return (failed_to_create_vital_thread(data));
	if (philo_nb % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&data->mutex_is_finish);
		if (data->end == 1)
		{
			pthread_mutex_unlock(&data->mutex_is_finish);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_is_finish);
		algo_philo(data, philo_nb);
	}
	pthread_join(check, NULL);
	return ((void *)0);
}
