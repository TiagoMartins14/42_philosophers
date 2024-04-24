/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/24 22:23:11 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// PRINTER

void	print_philos(t_thg *game, char *argv1)
{
	int i = 0;

	while (i++ < ft_atoi(argv1))
	{
		printf("\n*** PHILO %d ***\n", game->philosopher);
		printf("t_t_die %d\n", game->t_t_die);
		printf("t_t_eat %d\n", game->t_t_eat);
		printf("t_t_sleep %d\n", game->t_t_sleep);
		printf("max_meals %d\n", game->max_meals);
		printf("meals_counter %d\n", *game->meals_counter);
		printf("start_time %ld\n", *game->start_time);
		printf("dead %d\n", *game->dead);
		printf("philosopher %d\n", game->philosopher);
		printf("fork %d\n", game->fork);
		printf("current_time %ld\n", game->current_time);
		printf("last_meal %ld\n", game->last_meal);
		printf("eating %d\n", game->eating);
		printf("sleeping %d\n", game->sleeping);
		printf("thinking %d\n", game->thinking);
		printf("next %p\n", game->next);
		printf("prev %p\n", game->prev);
		game = game->next;
	}
}

void	*routine(void *args)
{
	t_thg	*table = args;
	long	timestamp;

	pthread_mutex_lock(table->time_mutex);
	while (*table->start_time == -1)
	{
		pthread_mutex_unlock(table->time_mutex);
		continue ;
	}
	pthread_mutex_unlock(table->time_mutex);
	if (table->philosopher % 2 == 0)
		ft_usleep(5, table);
	while (1)
	{
		timestamp = timestamp_calc(get_time_in_ms(), *table->start_time);
		timestamp -= timestamp % table->t_t_eat;
		pthread_mutex_lock(table->dead_mutex);
		if (timestamp - table->last_meal > table->t_t_die && *table->dead == false)
		{
			printf(RED"%ld %d died\n"RESET, timestamp + 1, table->philosopher);
			*table->dead = true;
			pthread_mutex_unlock(table->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(table->dead_mutex);
		if (has_two_forks(table) == true)
		{
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			table->last_meal = timestamp;
			printf(GREEN"%ld %d is eating\n"RESET, timestamp, table->philosopher);
			if (ft_usleep(table->t_t_eat * 1000, table) == 1)
				break ;
			pthread_mutex_lock(table->fork_mutex);
			table->fork = 0;
			table->prev->fork = 0;
			pthread_mutex_unlock(table->fork_mutex);
		}
		if (table->eating == true)
		{
			table->eating = false;
			table->sleeping = true;
			printf(BLUE"%ld %d is sleeping\n"RESET, timestamp + table->t_t_eat, table->philosopher);
			if (ft_usleep(table->t_t_sleep * 1000, table) == 1)
				break ;
			table->sleeping = false;
			table->thinking = true;
			printf("%ld %d is thinking\n", timestamp + table->t_t_sleep + table->t_t_eat, table->philosopher);
			table->thinking = false;
		}
		
	}
	return (args);
}

int	start_the_hunger_games(t_thg *table, int num_of_philos)
{
	pthread_t		philo[num_of_philos];
	pthread_mutex_t	time_mutex;
	t_thg			*chair;
	int				i;

	i = 0;
	chair = table;
	// mutex_handle(table->fork_mutex, INIT);
	// mutex_handle(table->dead_mutex, INIT);
	// mutex_handle(&time_mutex, INIT);
	while (i < num_of_philos)
	{
		chair->start_time = table->start_time;
		if (thread_handle(&philo[i], &routine, chair, CREATE) != 0)
			return (1);
		chair = chair->next;
		i++;
	}
	ft_usleep(100, table);
	mutex_handle(&time_mutex, LOCK);
	*table->start_time = get_time_in_ms();
	mutex_handle(&time_mutex, UNLOCK);
	i = 0;
	while (i < num_of_philos)
	{
		if (thread_handle(&philo[i], NULL, NULL, JOIN) != 0)
			return (1);
		i++;
	}
	// mutex_handle(table->fork_mutex, DESTROY);
	// mutex_handle(table->dead_mutex, DESTROY);
	// mutex_handle(&time_mutex, DESTROY);
	while (i < num_of_philos)
	{
		if (thread_handle(&philo[i], NULL, NULL, JOIN) != 0)
			return (1);
		i++;
	}
	return (0);
}



int	main(int argc, char **argv)
{
	int		i;
	t_thg	*table;
	t_thg	*chair;

	(void)argc;
	i = 1;
	if (ft_atoi(argv[1]) < 1)
		return (0);
	table = (t_thg *)malloc(sizeof(t_thg));
	t_thg_first_init(table, i, argv);
	table->next = table;
	table->prev = table;
	chair = table;
	while (++i <= ft_atoi(argv[1]))
	{
		chair->next = (t_thg *)malloc(sizeof(t_thg));
		t_thg_init(table, chair->next, i, argv);
		chair->next->prev = chair;
		chair->next->next = table;
		table->prev = chair->next;
		chair = chair->next;
	}
	start_the_hunger_games(table, ft_atoi(argv[1]));
}

// PARA FAZER:

// criar forma de um philo morrer no exato momento em que passar o t_t_die e ele nao tiver comido durante esse tempo.