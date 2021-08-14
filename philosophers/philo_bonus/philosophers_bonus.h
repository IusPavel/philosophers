/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:48:52 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:54:46 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>

enum e_boolean
{
	FALSE,
	TRUE
};
typedef sem_t	t_forks;
typedef struct s_source
{
	int				number_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_time_to_eat;
	sem_t			*event;
}		t_source;
typedef struct s_philo
{
	int				id;
	t_forks			*forks;
	unsigned long	number_time_to_eat;
	unsigned long	timestamp;
	unsigned long	lifetime;
	pid_t			pid;
	t_source		*init;
}				t_philo;
typedef struct s_waiter
{
	pthread_t	waiter;
	t_philo		*philo;
}				t_waiter;
int				ft_atoi(const char *str);
int				eaten(t_philo *this);
unsigned long	get_time(void);
void			act(t_philo *philo);
void			waiter_start(t_philo *this);
void			philo_free(t_source *source, t_philo *philos, int proc);
void			wait_children(t_source *source, t_philo *philos);
#endif
