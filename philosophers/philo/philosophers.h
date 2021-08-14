/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 08:34:51 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:53:41 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef pthread_mutex_t	t_fork;
typedef struct s_source
{
	int				number_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_time_to_eat;
	int				is_alive;
	pthread_mutex_t	event;
}		t_source;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_source		*init;
	unsigned long	number_time_to_eat;
	unsigned long	timestamp;
	unsigned long	lifetime;
}				t_philo;
typedef struct s_waiter
{
	pthread_t	waiter;
	t_philo		*philo;
}				t_waiter;
int				ft_atoi(const char *str);
int				eaten(t_philo *this);
unsigned long	get_time(void);
void			ft_millisleep(unsigned long time);
void			*act(void *philo);
void			*watch(void *philo);
int				print_msg(t_philo *this, char c);
int				philo_free(t_source *source, t_philo *philos, t_fork *forks);
#endif
