/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiago             #+#    #+#             */
/*   Updated: 2024/03/20 19:07:14 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

char	**argv_copy(char **argv)
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
}

void	t_events_init(t_events *philo, int i, char **argv)
{
	philo->philosopher = i;
	philo->fork = 0;
	philo->priority = i;
	philo->eating = 1;
	philo->sleeping = 1;
	philo->thinking = 1;
	philo->argv = argv_copy(argv);
	philo->next = NULL;
	philo->prev = NULL;
}

void	*routine(void *args)
{
	t_thread_args *arg;

	arg = (t_thread_args *)args;
	if ((t_thread_args *)arg->table_node->fork == 0 && arg->table_node->prev->fork == 0 && args->table_node->sleeping == 1 && args->table_node->thinking == 1)
	{
		arg->table_node->fork = 1;
		arg->table_node->prev->fork = 1;
		arg->table_node->eating = 0;
		printf("%d has taken a fork\n", arg->table_node->philosopher);
		printf("%d has taken a fork\n", arg->table_node->philosopher);
		printf("%d is eating\n", arg->table_node->philosopher);
	}
	// else if ()
}

int	start_hunger_games(char **argv, t_events *table, int num_of_philos)
{
	pthread_t		philo[num_of_philos];
	pthread_mutex_t	fork_mutex;
	t_thread_args	*args;
	int				i;

	args->argv = table->argv;
	args->table_node = table;
	pthread_mutex_init(&fork_mutex, NULL);
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_create(&philo[i], NULL, &routine, &args) != 0)
			return (1);
		i++;
	}
	pthread_mutex_destroy(&fork_mutex);
}



int	main(int argc, char **argv)
{
	int				i;
	int				num_of_philos;
	t_events		*table;
	t_events		*node;

	num_of_philos = ft_atoi(argv[1]);
	i = 1;
	if (num_of_philos < 1)
		return (0);
	table = (t_events *)malloc(sizeof(t_events));
	t_events_init(table, num_of_philos, argv);
	table->next = table;
	table->prev = table;
	node = table;
	while (++i <= num_of_philos)
	{	
		node->next = (t_events *)malloc(sizeof(t_events));
		t_events_init(node, num_of_philos, argv);
		node->next->prev = node;
		node->next->next = table;
		table->prev = node->next;
	}
}
