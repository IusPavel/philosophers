/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:49:08 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:54:56 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*dead_end(t_philo *this)
{
	sem_wait(this->init->event);
	if (this->number_time_to_eat != 0)
	{
		printf("%5lu %d died\n", get_time() - this->timestamp, this->id);
		exit(EXIT_FAILURE);
	}
	sem_post(this->init->event);
	return (NULL);
}

static void	*watch(void *philo)
{
	int				i;
	unsigned long	time_check;
	t_philo			*this;

	this = (t_philo *)philo;
	while (TRUE)
	{
		i = 0;
		time_check = get_time();
		if (time_check > this->lifetime + this->init->time_to_die)
			return (dead_end(this + i));
		i++;
		usleep(4000);
	}
	return (NULL);
}

void	waiter_start(t_philo *this)
{
	pthread_t	*waiter;

	waiter = (pthread_t *)malloc(sizeof(pthread_t));
	if (NULL == waiter)
	{
		printf("Error: memory not provided\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(waiter, NULL, watch, this))
	{
		printf("Error: thread is not created\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(*waiter))
	{
		printf("Error: detach is failed\n");
		exit (EXIT_FAILURE);
	}
}
