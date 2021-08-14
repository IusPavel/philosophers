/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 11:48:01 by signacia          #+#    #+#             */
/*   Updated: 2021/08/08 11:54:39 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	argv_check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n\
1st arg: number_of_philosophers\n2nd arg: time_to_die\n\
3rd arg: time_to_eat\n4th arg: time_to_sleep\n\
5th arg(optional): number_of_times_each_philosopher_must_eat\n");
		exit(EXIT_FAILURE);
	}
	while (argc != 1)
	{
		i = 0;
		while (argv[argc - 1][i])
		{
			if (!(argv[argc - 1][i] >= '0' && argv[argc - 1][i] <= '9'))
			{
				printf("Wrong argument %s\n", argv[argc - 1]);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		argc--;
	}
}

static void	initializer(t_source *init, int argc, char **argv)
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
		exit(EXIT_FAILURE);
	}
}

static void	memorizer(t_source *source, t_philo **philos, t_forks *forks)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * source->number_of_philo);
	if (NULL == *philos)
	{
		printf("Error: not enough memory\n");
		exit(EXIT_FAILURE);
	}
	forks = sem_open("philo_forks", O_CREAT, 0600, source->number_of_philo);
	source->event = sem_open("philo_event", O_CREAT, 0600, 1);
	if (SEM_FAILED == forks || SEM_FAILED == source->event)
	{
		printf("Error: semaphore_forks was not created\n");
		exit(EXIT_FAILURE);
	}
	memset(*philos, 0, sizeof(t_philo) * source->number_of_philo);
	i = 0;
	while (i < source->number_of_philo)
	{
		(*philos)[i].init = source;
		(*philos)[i].id = i + 1;
		(*philos)[i].forks = forks;
		(*philos)[i].number_time_to_eat = source->number_time_to_eat;
		i++;
	}
}

static void	process(t_source *source, t_philo *philos)
{
	int				i;
	unsigned long	timestamp;

	i = 0;
	timestamp = get_time();
	while (i < source->number_of_philo)
	{
		philos[i].timestamp = timestamp;
		philos[i].lifetime = timestamp;
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			act(philos + i);
		else if (philos[i].pid == -1)
		{
			printf("process (philo id=%d) is not created\n", i);
			philo_free(source, philos, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	wait_children(source, philos);
	philo_free(source, philos, -1);
}

int	main(int argc, char **argv)
{
	t_source	source;
	t_philo		*philosophers;
	t_forks		forks;

	sem_unlink("philo_forks");
	sem_unlink("philo_event");
	argv_check(argc, argv);
	initializer(&source, argc, argv);
	memorizer(&source, &philosophers, &forks);
	process(&source, philosophers);
	return (0);
}
