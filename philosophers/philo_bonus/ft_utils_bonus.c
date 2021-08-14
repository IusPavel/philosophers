/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:48:36 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:54:11 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

unsigned long	get_time(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void	philo_free(t_source *source, t_philo *philos, int proc)
{
	int	i;

	i = 0;
	while (i < proc)
		kill(philos[i++].pid, SIGKILL);
	i = 0;
	while (i < source->number_of_philo && philos[i].pid != 0)
		kill(philos[i++].pid, SIGKILL);
	sem_close(philos[0].forks);
	sem_unlink("philo_forks");
	sem_close(source->event);
	sem_unlink("philo_event");
	free(philos);
}

void	wait_children(t_source *source, t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < source->number_of_philo)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			printf("Error: waitpid failed\n");
			philo_free(source, philos, source->number_of_philo);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				philo_free(source, philos, source->number_of_philo);
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
}
