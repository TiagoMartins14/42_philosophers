/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/26 15:00:41 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_usleep(int usec)
{
	struct timeval	start; 
	struct timeval	current;
	long			elapsed_usec;

	if (gettimeofday(&start, NULL) == -1)
	{
		write(2, "gettimeofday error\n", 20);
		return (-1);
	}
	while (1)
	{
		if (gettimeofday(&current, NULL) == -1)
		{
			write(2, "gettimeofday error\n", 20);
			return (-1);
		}
		elapsed_usec = (current.tv_sec - start.tv_sec) * 1000000
			+ (current.tv_usec - start.tv_usec);
		if (elapsed_usec >= usec)
			break ;
		usleep (100);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday error\n", 20);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	timestamp_calc(long current_time, long start_time)
{
	return (current_time - start_time);
}

void	*routine(void *args)
{
	t_thg	*table = args;
	long	timestamp;

	while (*table->start_time == -1)
		continue ;
	while (1)
	{
		timestamp = timestamp_calc(get_time(), *table->start_time);
		pthread_mutex_lock(&table->fork_mutex);
		if (table->fork == 0 && table->prev->fork == 0 && table->sleeping == false)
		{
			table->fork = 1;
			table->prev->fork = 1;
			pthread_mutex_unlock(&table->fork_mutex);
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
			table->eating = true;
			printf(GREEN"%ld %d is eating\n"RESET, timestamp, table->philosopher);
			ft_usleep(table->argv_3 * 1000);
			pthread_mutex_lock(&table->fork_mutex);
			table->fork = 0;
			table->prev->fork = 0;
		}
		pthread_mutex_unlock(&table->fork_mutex);
		if (table->eating == true)
		{
			table->eating = false;
			table->sleeping = true;
			printf("%ld %d is sleeping\n", timestamp + table->argv_3, table->philosopher);
			ft_usleep(table->argv_4 * 1000);
			table->sleeping = false;
			table->thinking = true;
			printf("%ld %d is thinking\n", timestamp + table->argv_4, table->philosopher);
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
	// table->start_time = get_time();
	while (i < num_of_philos)
	{
		chair->start_time = table->start_time;
		if (pthread_create(&philo[i], NULL, &routine, chair) != 0)
			return (1);
		chair->all_set = true;
		chair = chair->next;
		i++;
	}
	sleep(1);
	*set_start = get_time();
	while (chair)
	{
		if (chair->dead == true)
			return (0);
		chair = chair->next;
	}
	pthread_mutex_destroy(&table->fork_mutex);
	return (0);
}



int	main(int argc, char **argv)
{
	int		i;
	int		num_of_philos;
	long	*set_start;
	t_thg	*table;
	t_thg	*chair;

	(void)argc;
	num_of_philos = ft_atoi(argv[1]);
	i = 1;
	if (num_of_philos < 1)
		return (0);
	set_start = malloc(sizeof(int));
	*set_start = -1;
	table = (t_thg *)malloc(sizeof(t_thg));
	t_thg_init(table, i, set_start, argv);
	table->next = table;
	table->prev = table;
	chair = table;
	while (++i <= num_of_philos)
	{
		chair->next = (t_thg *)malloc(sizeof(t_thg));
		t_thg_init(chair->next, i, set_start, argv);
		chair->next->prev = chair;
		chair->next->next = table;
		table->prev = chair->next;
		chair = chair->next;
	}
	start_the_hunger_games(table, num_of_philos, set_start);
}
