/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:42:06 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/30 19:51:07 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_usleep(long usec, t_thg *thg)
{
	long	start; 
	long	elapsed;
	long	rem;
	(void)(thg);
	start = get_time_in_ms() * 1e3;
	while (get_time_in_ms() * 1e3 - start < usec)
	{
		if (game_over_condition_met(thg))
			break ;
		elapsed = get_time_in_ms() * 1e3 - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (get_time_in_ms() * 1e3 - start < usec)
				;
	}
	return ;
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
