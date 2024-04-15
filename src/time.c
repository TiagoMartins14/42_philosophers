/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:42:06 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/15 16:43:42 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_usleep(int usec, t_thg *table)
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
		pthread_mutex_lock(table->dead_mutex);
		if (*table->dead == true)
		{
			pthread_mutex_unlock(table->dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(table->dead_mutex);
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
