/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 08:35:02 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:53:26 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	thinking(t_philo *this)
{
	print_msg(this, 't');
	usleep(200);
	return (0);
}

static int	eating(t_philo *this)
{
	if (this->init->is_alive == 0)
		return (1);
	pthread_mutex_lock(this->left_fork);
	print_msg(this, 'f');
	pthread_mutex_lock(this->right_fork);
	print_msg(this, 'f');
	print_msg(this, 'e');
	this->lifetime = get_time();
	ft_millisleep(this->init->time_to_eat);
	pthread_mutex_unlock(this->left_fork);
	pthread_mutex_unlock(this->right_fork);
	if (this->number_time_to_eat > 0)
	{
		this->number_time_to_eat--;
		if (this->number_time_to_eat == 0)
			return (1);
	}
	return (0);
}

static int	sleeping(t_philo *this)
{
	print_msg(this, 's');
	ft_millisleep(this->init->time_to_sleep);
	return (0);
}

void	*act(void *philo)
{
	t_philo		*this;

	this = (t_philo *)philo;
	if (this->id % 2 == 0)
		thinking(this);
	while (1)
	{
		if (eating(this)
			|| sleeping(this)
			|| thinking(this))
			return (NULL);
	}
	return (NULL);
}
