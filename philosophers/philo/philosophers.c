/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 08:34:32 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:53:36 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	argv_check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n\
1st arg: number_of_philosophers\n2nd arg: time_to_die\n\
3rd arg: time_to_eat\n4th arg: time_to_sleep\n\
5th arg(optional): number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	while (argc != 1)
	{
		i = 0;
		while (argv[argc - 1][i])
		{
			if (!(argv[argc - 1][i] >= '0' && argv[argc - 1][i] <= '9'))
			{
				printf("Wrong argument %s\n", argv[argc - 1]);
				return (1);
			}
			i++;
		}
		argc--;
	}
	return (0);
}

static int	initializer(t_source *init, int argc, char **argv)
{
	init->number_of_philo = ft_atoi(argv[1]);
	init->time_to_die = ft_atoi(argv[2]);
	init->time_to_eat = ft_atoi(argv[3]);
	init->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		init->number_time_to_eat = ft_atoi(argv[5]);
	else
		init->number_time_to_eat = -1;
	if (init->number_of_philo <= 0
		|| init->time_to_die <= 0
		|| init->time_to_eat <= 0
		|| init->time_to_sleep <= 0)
	{
		printf("Invalid parameters\n");
		return (1);
	}
	init->is_alive = 1;
	return (0);
}

static int	memorizer(t_source *source, t_philo **philos, t_fork **forks)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * source->number_of_philo);
	*forks = (t_fork *)malloc(sizeof(t_fork) * source->number_of_philo);
	if (*philos == NULL || *forks == NULL)
		return (printf("Error: memory not provided\n"));
	if (pthread_mutex_init(&source->event, NULL) != 0)
		return (printf("Error while initializing mutex\n"));
	i = 0;
	while (i < source->number_of_philo)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
			return (printf("Error while initializing mutex\n"));
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % source->number_of_philo];
		(*philos)[i].init = source;
		(*philos)[i].number_time_to_eat = source->number_time_to_eat;
		i++;
	}
	return (0);
}

int	process(t_source *source, t_philo *philos, t_fork *forks, t_waiter *waiter)
{
	int				i;
	unsigned long	timestamp;

	i = 0;
	timestamp = get_time();
	while (i < source->number_of_philo)
	{
		philos[i].timestamp = timestamp;
		philos[i].lifetime = timestamp;
		if (pthread_create(&philos[i].thread, NULL, act, &philos[i]))
			return (printf("Error: thread is not created\n"));
		i++;
	}
	if (pthread_create(&waiter->waiter, NULL, watch, philos))
		return (printf("Error: thread is not created\n"));
	i = 0;
	while (i < source->number_of_philo)
		if (pthread_detach(philos[i++].thread))
			return (printf("Error: detach is failed\n"));
	if (pthread_join(waiter->waiter, NULL))
		return (printf("Error: join is failed\n"));
	return (philo_free(source, philos, forks));
}

int	main(int argc, char **argv)
{
	t_source	source;
	t_philo		*philosophers;
	t_fork		*forks;
	t_waiter	waiter;

	if (argv_check(argc, argv)
		|| initializer(&source, argc, argv)
		|| memorizer(&source, &philosophers, &forks)
		|| process(&source, philosophers, forks, &waiter))
		return (1);
	return (0);
}
