/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 08:34:07 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:53:05 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i++];
		result -= '0';
	}
	result *= sign;
	return (result);
}

int	philo_free(t_source *source, t_philo *philos, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < source->number_of_philo)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(&source->event);
	free(philos);
	free(forks);
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void	ft_millisleep(unsigned long time)
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

int	print_msg(t_philo *this, char c)
{
	pthread_mutex_lock(&this->init->event);
	if (this->init->is_alive == 1)
	{
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
	}
	pthread_mutex_unlock(&this->init->event);
	return (1);
}
