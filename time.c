/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:42:06 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/02 12:32:37 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long usec, t_thg *thg)
{
	long	start;

	start = get_time_in_ms() * 1e3;
	while (get_time_in_ms() * 1e3 - start < usec)
	{
		if (game_over_condition_met(thg))
			break ;
		usleep(100);
	}
	return ;
}

long	get_time_in_ms(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}
