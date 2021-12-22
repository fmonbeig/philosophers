/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:14:03 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/13 17:53:02 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	use_fork(t_data *data, int i)
{
	int	left;
	int	right;

	left = i % data->philo;
	right = i - 1;
	if (i % 2)
	{
		pthread_mutex_lock(&data->fork[left]);
		message("has taken a fork", i, data);
		pthread_mutex_lock(&data->fork[right]);
		message("has taken a fork", i, data);
	}
	else
	{
		pthread_mutex_lock(&data->fork[right]);
		message("has taken a fork", i, data);
		pthread_mutex_lock(&data->fork[left]);
		message("has taken a fork", i, data);
	}
}

void	put_down_fork(t_data *data, int i)
{
	int	left;
	int	right;

	left = i % data->philo;
	right = i - 1;
	if (i % 2)
	{
		pthread_mutex_unlock(&data->fork[right]);
		pthread_mutex_unlock(&data->fork[left]);
	}
	else
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->fork[right]);
	}
}
