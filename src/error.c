/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:03:31 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/11/03 16:37:39 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_argument(int argc, char **argv)
{
	int	i;
	int	j;

	if (error_nb_argument(argc) || error_philo_zero(argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				ft_putstr_fd("ERROR :", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(" is negative or not a digit\n", 2);
				return (1);
			}
		}
	}
	return (0);
}

int	error_philo_zero(char **argv)
{
	int	i;

	i = -1;
	while (argv[1][++i])
	{
		if (argv[1][i] != '0')
			return (0);
	}
	ft_putstr_fd("ERROR : 0 Philo = 0 Program \n", 2);
	return (1);
}

int	error_nb_argument(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("ERROR : only 4 or 5 arguments required\n", 2);
		return (1);
	}
	return (0);
}
