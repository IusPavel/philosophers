/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:48:19 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:54:31 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	print_msg(t_philo *this, char c)
{
	sem_wait(this->init->event);
	if (c == 'f')
		printf("%5lu %d has taken a fork\n",
			get_time() - this->timestamp, this->id);
	else if (c == 'e')
		printf("%5lu %d is eating\n",
			get_time() - this->timestamp, this->id);
	else if (c == 't')
		printf("%5lu %d is thinking\n",
			get_time() - this->timestamp, this->id);
	else if (c == 's')
		printf("%5lu %d is sleeping\n",
			get_time() - this->timestamp, this->id);
	sem_post(this->init->event);
}

static void	ft_millisleep(unsigned long time)
{
	unsigned long	start;
	unsigned long	now;

	start = get_time();
	now = start;
	while (time > now - start)
	{
		now = get_time();
		usleep(100);
	}
}

static void	eating(t_philo *this)
{
	sem_wait(this->forks);
	print_msg(this, 'f');
	sem_wait(this->forks);
	print_msg(this, 'f');
	print_msg(this, 'e');
	this->lifetime = get_time();
	ft_millisleep(this->init->time_to_eat);
	sem_post(this->forks);
	sem_post(this->forks);
	if (this->number_time_to_eat > 0)
	{
		this->number_time_to_eat--;
		if (this->number_time_to_eat == 0)
			exit(EXIT_SUCCESS);
	}
}

void	act(t_philo *this)
{
	waiter_start(this);
	if (this->id % 2 == 0)
	{
		print_msg(this, 't');
		usleep(200);
	}
	while (TRUE)
	{
		eating(this);
		print_msg(this, 's');
		ft_millisleep(this->init->time_to_sleep);
		print_msg(this, 't');
		usleep(200);
	}
}
