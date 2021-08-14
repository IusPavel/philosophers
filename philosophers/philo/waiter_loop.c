/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:37:41 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:53:52 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*dead_end(t_philo *this)
{
	pthread_mutex_lock(&this->init->event);
	this->init->is_alive = 0;
	if (this->number_time_to_eat != 0)
		printf("%5lu %d died\n", get_time() - this->timestamp, this->id);
	pthread_mutex_unlock(&this->init->event);
	return (NULL);
}

void	*watch(void *philo)
{
	int				i;
	unsigned long	time_check;
	t_philo			*this;

	this = (t_philo *)philo;
	while (1)
	{
		i = 0;
		time_check = get_time();
		while (i < this->init->number_of_philo)
		{
			if (time_check > this[i].lifetime + this[i].init->time_to_die)
				return (dead_end(this + i));
			i++;
		}
		usleep(3000);
	}
	return (NULL);
}
