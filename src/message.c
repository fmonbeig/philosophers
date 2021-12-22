/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:58:27 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/10 12:07:29 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	message(char *str, int i, t_data *data)
{
	struct timeval	now;
	long int		time;
	long int		start;
	int				forever;

	forever = 1;
	pthread_mutex_lock(&data->mutex_is_finish);
	if (data->end == 1)
		forever = 0;
	pthread_mutex_unlock(&data->mutex_is_finish);
	pthread_mutex_lock(&data->mutex_message);
	if (forever)
	{
		gettimeofday(&now, NULL);
		start = (data->start.tv_sec * 1000000 + data->start.tv_usec) / 1000;
		time = ((now.tv_sec * 1000000 + now.tv_usec) / 1000) - start;
		printf("%ld   %d %s\n", time, i, str);
	}
	pthread_mutex_unlock(&data->mutex_message);
}
