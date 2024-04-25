/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:42:06 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/25 09:49:31 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_usleep(long usec, t_thg *table)
{
	long	start; 
	long	elapsed;
	long	rem;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < usec)
	{
		if (game_over_condition_met(table))
			break ;
		elapsed = get_time_in_ms() - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_time_in_ms() - start < usec)
				;
	}
	return (0);
}

long	get_time_in_ms(void)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday error\n", 20);
		return (-1);
	}
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

long	timestamp_calc(long current_time, long start_time)
{
	return (current_time - start_time);
}
