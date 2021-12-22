/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:10:55 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/13 17:38:15 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo);
	while (++i < data->philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&data->mutex_nb, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_eat_or_alive, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_is_finish, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_round_reach, NULL) != 0)
		return (1);
	return (0);
}

static int	init_finish(t_data *data)
{
	int	i;

	i = -1;
	if (data->round > 0)
	{
		data->finish = malloc(sizeof(int *) * data->philo);
		if (!data->finish)
			return (1);
		while (++i < data->philo)
			data->finish[i] = 0;
	}
	else
		data->finish = NULL;
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->temp = 0;
	data->philo = ft_atoi(argv[1]);
	data->death = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->round = ft_atoi(argv[5]);
	else
		data->round = 0;
	gettimeofday(&data->start, NULL);
	data->last_meal = malloc(sizeof(struct timeval) * data->philo);
	data->phil = malloc(sizeof(pthread_t) * data->philo);
	if (!data->last_meal || !data->phil)
		return (1);
	data->end = 0;
	if (init_finish(data))
		return (1);
	if (init_mutex(data))
		return (1);
	return (0);
}

int	init_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo)
		gettimeofday(&data->last_meal[i], NULL);
	i = -1;
	while (++i < data->philo)
	{
		if (pthread_create(&data->phil[i], NULL, &philosophers, data) != 0)
		{
			ft_putstr_fd("ERROR:failed to create a thread", 2);
			return (1);
		}
	}
	return (0);
}
