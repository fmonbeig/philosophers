/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:18:50 by fmonbeig          #+#    #+#             */
/*   Updated: 2021/12/09 17:44:07 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// +------------------------------------------+ //
//   System header files                        //
// +------------------------------------------+ //

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <linux/limits.h>
# include <pthread.h>

// +------------------------------------------+ //
//   Define                                     //
// +------------------------------------------+ //

// +------------------------------------------+ //
//   Type definition                            //
// +------------------------------------------+ //
typedef struct s_data
{
	int				temp;
	int				end;
	int				philo;
	int				*finish;
	int				round;
	long int		death;
	long int		eat;
	long int		sleep;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_nb;
	pthread_mutex_t	mutex_message;
	pthread_mutex_t	mutex_eat_or_alive;
	pthread_mutex_t	mutex_is_finish;
	pthread_mutex_t	mutex_round_reach;
	pthread_t		*phil;
	struct timeval	start;
	struct timeval	*last_meal;
}		t_data;
// +------------------------------------------+ //
//   Main                                       //
// +------------------------------------------+ //
int			main(int argc, char **argv);
void		lock_end(t_data *data);
// +------------------------------------------+ //
//   Init                                       //
// +------------------------------------------+ //
int			init_data(t_data *data, int argc, char **argv);
// +------------------------------------------+ //
//   Close                                      //
// +------------------------------------------+ //
void		destroy_mutex(t_data *data);
void		close_thread(t_data *data);
void		free_malloc(t_data *data);
void		unlock_all(t_data *data);
// +------------------------------------------+ //
//   State                                      //
// +------------------------------------------+ //
void		algo_philo(t_data *data, int philo_nb);
// +------------------------------------------+ //
//   Fork                                       //
// +------------------------------------------+ //
void		use_fork(t_data *data, int i);
void		put_down_fork(t_data *data, int i);
// +------------------------------------------+ //
//   Thread                                     //
// +------------------------------------------+ //
void		*philosophers(void *temp);
void		*check_vital(void *temp);
int			init_thread(t_data *data);
// +------------------------------------------+ //
//   Algo                                       //
// +------------------------------------------+ //
void		algo(t_data *data, int philo_nb);
// +------------------------------------------+ //
//   Utils Philo                                //
// +------------------------------------------+ //
int			check_round(t_data *data);
long int	get_alive(int philo_nb, t_data *data);
void		dead(int philo_nb, t_data *data);
void		round_reach(int philo_nb, t_data *data);
// +------------------------------------------+ //
//   Utils Libft                                //
// +------------------------------------------+ //
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
// +------------------------------------------+ //
//   Error                                      //
// +------------------------------------------+ //
int			error_argument(int argc, char **argv);
int			error_philo_zero(char **argv);
int			error_nb_argument(int argc);
// +------------------------------------------+ //
//   Message                                    //
// +------------------------------------------+ //
void		message(char *str, int i, t_data *data);

#endif
