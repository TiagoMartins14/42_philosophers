/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:42:06 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 10:32:38 by tiaferna         ###   ########.fr       */
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
		if (elapsed_usec >= usec || *table->dead == true)
			break ;
		if (grim_reaper_arrived(table, elapsed_usec) == true)
		{
			is_dead(table, elapsed_usec);
			return (1);
		}
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
