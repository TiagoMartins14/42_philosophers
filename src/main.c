/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiago             #+#    #+#             */
/*   Updated: 2024/03/23 23:19:26 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	t_events_init(t_events *philo, int i, char **argv)
{
	philo->argv_1 = ft_atoi(argv[1]);
	philo->argv_2 = ft_atoi(argv[2]);
	philo->argv_3 = ft_atoi(argv[3]);
	philo->argv_4 = ft_atoi(argv[4]);
	if (argv[5])
		philo->argv_5 = ft_atoi(argv[5]);
	else
		philo->argv_5 = -1;
	philo->philosopher = i;
	philo->fork = 0;
	philo->priority = i;
	philo->eating = false;
	philo->sleeping = false;
	philo->thinking = false;
	philo->dead = false;
	philo->next = NULL;
	philo->prev = NULL;
}

void	*routine(void * args)
{
	t_events *table = args;
	
	while (1)
	{
		if (table->fork == 0 && table->prev->fork == 0 && table->sleeping == false)
		{
			table->fork = 1;
			table->prev->fork = 1;
			gettimeofday(&table->current_time, NULL);
			printf("%ld %d has taken a fork\n", table->current_time.tv_usec, table->philosopher);
			gettimeofday(&table->current_time, NULL);
			printf("%ld %d has taken a fork\n", table->current_time.tv_usec, table->philosopher);
			table->eating = true;
			gettimeofday(&table->current_time, NULL);
			printf("%ld %d is eating\n", table->current_time.tv_usec, table->philosopher);
			usleep(table->argv_3);
			table->fork = 0;
			table->prev->fork = 0;
			table->eating = false;
			table->sleeping = true;
			printf("%ld %d is sleeping\n", table->current_time.tv_usec, table->philosopher);
			usleep(table->argv_4);
			table->sleeping = false;
			table->thinking = true;
			printf("%ld %d is thinking\n", table->current_time.tv_usec, table->philosopher);
			table->thinking = false;
		}
	}
	return (args);
}

int	start_hunger_games(t_events *table, int num_of_philos)
{
	pthread_t		philo[num_of_philos];
	pthread_mutex_t	fork_mutex;
	int				i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&fork_mutex, NULL);
		if (pthread_create(&philo[i], NULL, &routine, table) != 0)
			return (1);
		pthread_mutex_destroy(&fork_mutex);
		table = table->next;
		i++;
	}
	while (table)
	{
		if (table->dead == true)
			return (0);
		// usleep(50);
		table = table->next;
	}
	return (0);
}



int	main(int argc, char **argv)
{
	int				i;
	int				num_of_philos;
	t_events		*table;
	t_events		*node;

	(void)argc;
	num_of_philos = ft_atoi(argv[1]);
	i = 1;
	if (num_of_philos < 1)
		return (0);
	table = (t_events *)malloc(sizeof(t_events));
	t_events_init(table, i, argv);
	gettimeofday(&table->start_time, NULL);
	table->next = table;
	table->prev = table;
	node = table;
	while (++i <= num_of_philos)
	{
		node->next = (t_events *)malloc(sizeof(t_events));
		t_events_init(node->next, i, argv);
		node->next->prev = node;
		node->next->next = table;
		table->prev = node->next;
		node = node->next;
	}
	start_hunger_games(table, num_of_philos);
	// while (node != table)
	// {
	// 	int j = 0;
	// 	printf("eating: %d\n", node->eating);
	// 	printf("fork: %d\n", node->fork);
	// 	printf("philosopher: %d\n", node->philosopher);
	// 	printf("priority: %d\n", node->priority);
	// 	printf("sleeping: %d\n", node->sleeping);
	// 	printf("thinking %d\n\n", node->thinking);
	// 	printf("argv:");
	// 	while (node->argv[j])
	// 		printf(" %s", node->argv[j++]);
	// 	printf("\n");
	// 	node = node->prev;
	// }
	// printf("eating: %d\n", node->eating);
	// printf("fork: %d\n", node->fork);
	// printf("philosopher: %d\n", node->philosopher);
	// printf("priority: %d\n", node->priority);
	// printf("sleeping: %d\n", node->sleeping);
	// printf("thinking %d\n", node->thinking);
}
