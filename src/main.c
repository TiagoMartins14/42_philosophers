/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiago             #+#    #+#             */
/*   Updated: 2024/03/23 20:14:04 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* char	**argv_copy(char **argv)
{
	int		i;
	char	**argv_copy;

	i = 0;
	while (argv[i])
		i++;
	argv_copy = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (argv[i])
	{
		argv_copy[i] = ft_strdup(argv[i]);
		i++;
	}
	argv_copy[i] = NULL;
	return (argv_copy);
} */

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
	philo->eating = 1;
	philo->sleeping = 1;
	philo->thinking = 1;
	philo->dead = 1;
	philo->next = NULL;
	philo->prev = NULL;
}

void	*routine(void * args)
{
	t_events *table = args;
	while (1)
	{
		if (table->fork == 0 && table->prev->fork == 0 && table->sleeping == 1 && table->thinking == 1)
		{
			table->fork = 1;
			table->prev->fork = 1;
			table->eating = 0;
			printf("%d has taken a fork\n", table->philosopher);
			printf("%d has taken a fork\n", table->philosopher);
			printf("%d is eating\n", table->philosopher);
			sleep(table->argv_3);
			printf("%d is sleeping\n", table->philosopher);
			sleep(table->argv_4);
			table->fork = 0;
			table->prev->fork = 0;
		}
	}
	return (args);
}

int	start_hunger_games(t_events *table, int num_of_philos)
{
	pthread_t		philo[num_of_philos];
	pthread_mutex_t	fork_mutex;
	int				i;

	// pthread_mutex_init(&fork_mutex, NULL);
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
		if (table->dead == 0)
			return (0);
		usleep(5000);
		table = table->next;
	}

	// pthread_mutex_destroy(&fork_mutex);
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
