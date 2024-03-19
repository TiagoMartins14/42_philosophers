/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiago             #+#    #+#             */
/*   Updated: 2024/03/19 23:26:42 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_events
{
	int				philosopher;
	int				fork;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	struct s_events	*next;
	struct s_events	*prev;
}	t_events;

void	t_events_init(t_events *philo, int i)
{
	philo->philosopher = i;
	philo->fork = 0;
	philo->eating = 1;
	philo->sleeping = 1;
	philo->thinking = 1;
	philo->next = NULL;
	philo->prev = NULL;
}

int	ft_atoi(const char *nstr)
{
	size_t	i;
	int		sign;
	int		nb;

	nb = 0;
	sign = 1;
	i = 0;
	while ((nstr[i] >= 9 && nstr[i] <= 13) || nstr[i] == 32)
		i++;
	if (nstr[i] == '-' || nstr[i] == '+')
	{
		if (nstr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nstr[i] >= '0' && nstr[i] <= '9')
		nb = nb * 10 + nstr[i++] - '0';
	return (nb * sign);
}

void	*routine(t_events *table_node, char *argv)
{
	if (table_node->fork == 0 && table_node->prev->fork == 0 && table_node->sleeping == 1 && table_node->thinking == 1)
	{
		table_node->fork = 1;
		table_node->prev->fork = 1;
		table_node->eating = 0;
		printf("%d has taken a fork\n", table_node->philosopher);
		printf("%d has taken a fork\n", table_node->philosopher);
		printf("%d is eating\n", table_node->philosopher);
	}
	else if ()
}

int	start_hunger_games(char **argv, t_events *table, int num_of_philos)
{
	pthread_t		philo[num_of_philos];
	pthread_mutex_t	fork_mutex;
	int				i;

	pthread_mutex_init(&fork_mutex, NULL);
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_create(&philo[i], NULL, &routine, NULL) != 0)
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
	t_events_init(table, num_of_philos);
	table->next = table;
	table->prev = table;
	node = table;
	while (++i <= num_of_philos)
	{	
		node->next = (t_events *)malloc(sizeof(t_events));
		t_events_init(node, num_of_philos);
		node->next->prev = node;
		node->next->next = table;
		table->prev = node->next;
	}
}
