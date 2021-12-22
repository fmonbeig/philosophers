/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:13:20 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/10 12:09:05 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (error_argument(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
	{
		free_malloc(&data);
		return (1);
	}
	if (init_thread(&data))
	{
		free_malloc(&data);
		return (1);
	}
	lock_end(&data);
	close_thread(&data);
	destroy_mutex(&data);
	free_malloc(&data);
	return (0);
}

void	lock_end(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_is_finish);
		if (data->end == 1)
		{
			pthread_mutex_unlock(&data->mutex_is_finish);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_is_finish);
		usleep(50);
	}
}
