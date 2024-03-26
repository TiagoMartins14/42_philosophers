/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/26 22:09:34 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *args)
{
	t_thg	*table = args;
	long	timestamp;

	while (*table->start_time == -1)
		continue ;
	while (1)
	{
		timestamp = timestamp_calc(get_time(), *table->start_time);
		timestamp -= timestamp % table->t_t_eat;
		if (timestamp - table->last_meal > table->t_t_die && *table->dead == false)
		{
			printf(RED"%ld %d died\n"RESET, timestamp, table->philosopher);
			*table->dead = true;
			break ;
		}
		if (has_two_forks(table) == true)
		{
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			table->last_meal = timestamp;
			printf(GREEN"%ld %d is eating\n"RESET, timestamp, table->philosopher);
			ft_usleep(table->t_t_eat * 1000);
			pthread_mutex_lock(&table->fork_mutex);
			table->fork = 0;
			table->prev->fork = 0;
			pthread_mutex_unlock(&table->fork_mutex);
		}
		if (table->eating == true)
		{
			table->eating = false;
			table->sleeping = true;
			printf("%ld %d is sleeping\n", timestamp + table->t_t_eat, table->philosopher);
			ft_usleep(table->t_t_sleep * 1000);
			table->sleeping = false;
			table->thinking = true;
			printf("%ld %d is thinking\n", timestamp + table->t_t_sleep + table->t_t_eat, table->philosopher);
			table->thinking = false;
		}
	}
	return (args);
}

int	start_the_hunger_games(t_thg *table, int num_of_philos, long *set_start)
{
	pthread_t		philo[num_of_philos];
	t_thg			*chair;
	int				i;

	i = 0;
	chair = table;
	pthread_mutex_init(&table->fork_mutex, NULL);
	while (i < num_of_philos)
	{
		chair->start_time = table->start_time;
		if (pthread_create(&philo[i], NULL, &routine, chair) != 0)
			return (1);
		chair = chair->next;
		i++;
	}
	sleep(1);
	*set_start = get_time();
	while (chair)
	{
		if (*chair->dead == true)
			return (0);
		chair = chair->next;
	}
	pthread_mutex_destroy(&table->fork_mutex);
	return (0);
}



int	main(int argc, char **argv)
{
	int		i;
	long	*set_start;
	bool	*death;
	t_thg	*table;
	t_thg	*chair;

	(void)argc;
	i = 1;
	if (ft_atoi(argv[1]) < 1)
		return (0);
	set_start = malloc(sizeof(int));
	*set_start = -1;
	death = malloc(sizeof(bool));
	*death = false;
	table = (t_thg *)malloc(sizeof(t_thg));
	t_thg_init(table, i, argv);
	t_thg_common_var_setter(table, set_start, death);
	table->next = table;
	table->prev = table;
	chair = table;
	while (++i <= ft_atoi(argv[1]))
	{
		chair->next = (t_thg *)malloc(sizeof(t_thg));
		t_thg_init(chair->next, i, argv);
		t_thg_common_var_setter(chair->next, set_start, death);
		chair->next->prev = chair;
		chair->next->next = table;
		table->prev = chair->next;
		chair = chair->next;
	}
	start_the_hunger_games(table, ft_atoi(argv[1]), set_start);
}

// A FAZER:
// Parar mal um philo chegue ao t_t_die sem ter comido nada.