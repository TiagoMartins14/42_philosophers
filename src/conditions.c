/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:25:29 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/15 16:40:32 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	has_two_forks(t_thg *table)
{
	pthread_mutex_lock(table->fork_mutex);
	if (table->fork == 0 && table->prev->fork == 0 && table->sleeping == false)
	{
		table->fork = 1;
		table->prev->fork = 1;
		table->eating = true;
	}
	pthread_mutex_unlock(table->fork_mutex);
	if (table->eating == true)
		return (true);
	else
		return (false);
}

bool	is_philo_dead(t_thg *table)
{
	pthread_mutex_lock(table->dead_mutex);
	if (*table->dead == true)
	{
		pthread_mutex_unlock(table->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(table->dead_mutex);
	return (false);
}
