/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/15 08:10:46 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *args)
{
	t_thg	*table = args;
	long	timestamp;

	while (*table->start_time == -1)
		continue ;
	if (table->philosopher % 2 == 0)
		ft_usleep(5, table);
	while (1)
	{
		timestamp = timestamp_calc(get_time(), *table->start_time);
		timestamp -= timestamp % table->t_t_eat;
		// printf("time: %ld	t_t_die: %d\n", (timestamp - table->last_meal) * 1000, table->t_t_die * 1000);
		if (grim_reaper_arrived(table, (timestamp - table->last_meal) * 1000) == true)
		{
			is_dead(table, timestamp);
			break;
		}
		if (has_two_forks(table) == true)
		{
			philo_eat(table, timestamp);
			if (ft_usleep(table->t_t_eat * 1000, table) == 1 || death_checker(table) == true)
				break;
			prepare_to_sleep(table);
			if (ft_usleep(table->t_t_sleep * 1000, table) == 1 || death_checker(table) == true)
				break;
			philo_sleep(table, timestamp);
			if (death_checker(table) == true)
				break;
			philo_think(table,timestamp);
		}
	}
	return (args);
}

int	start_the_hunger_games(t_thg *table, int num_of_philos, long *set_start)
{
	pthread_t		philo[num_of_philos];
	t_thg			*chair;
	int				i;

	(void)set_start;
	i = 0;
	chair = table;
	pthread_mutex_init(&table->fork_mutex, NULL);
	pthread_mutex_init(&table->dead_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	while (i < num_of_philos)
	{
		chair->start_time = table->start_time;
		if (pthread_create(&philo[i], NULL, &routine, chair) != 0)
			return (1);
		chair = chair->next;
		i++;
	}
	ft_usleep(100, table);
	*table->start_time = get_time();
	while (chair)
	{
		pthread_mutex_lock(&table->dead_mutex);
		if (*chair->dead == true)
		{
			pthread_mutex_unlock(&table->dead_mutex);
			break ;
		}
		chair = chair->next;
		pthread_mutex_unlock(&table->dead_mutex);
	}
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->fork_mutex);
	pthread_mutex_destroy(&table->print_mutex);
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
	free_the_games(table);
}
