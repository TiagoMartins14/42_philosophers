/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:25:29 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 10:55:55 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	has_two_forks(t_thg *table)
{
	pthread_mutex_lock(&table->fork_mutex);
	if (table->fork == 0 && table->prev->fork == 0 && table->sleeping == false)
	{
		table->fork = 1;
		table->prev->fork = 1;
		table->eating = true;
	}
	pthread_mutex_unlock(&table->fork_mutex);
	if (table->eating == true)
		return (true);
	else
		return (false);
}

bool	is_dead(t_thg *table, long timestamp)
{
	(void)timestamp;
	// pthread_mutex_lock(&table->dead_mutex);
	// if (*table->dead == false)
	// {
	// 	*table->dead = true;
	// 	pthread_mutex_unlock(&table->dead_mutex);
		pthread_mutex_lock(&table->print_mutex);
		printf(RED"%ld %d died\n"RESET, table->last_meal + table->t_t_die + 1, table->philosopher);
		pthread_mutex_unlock(&table->print_mutex);
		// return (true);
	// }
	// pthread_mutex_unlock(&table->dead_mutex);
	return (true);
}

bool	death_checker(t_thg *table)
{
	pthread_mutex_lock(&table->dead_mutex);
	if (*table->dead == true)
	{
		pthread_mutex_unlock(&table->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->dead_mutex);
	return (false);
}

bool	grim_reaper_arrived(t_thg *table, long elapsed_usec)
{
	pthread_mutex_lock(&table->dead_mutex);
	if (elapsed_usec > table->t_t_die && *table->dead == false)
	{
		*table->dead = true;
		pthread_mutex_unlock(&table->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->dead_mutex);
	return (false);
}
