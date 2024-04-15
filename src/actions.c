/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:37:44 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 11:11:27 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_eat(t_thg *table, long timestamp)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d has taken a fork\n", timestamp, table->philosopher);
	pthread_mutex_unlock(&table->print_mutex);
	table->last_meal = timestamp;
	pthread_mutex_lock(&table->print_mutex);
	printf(GREEN"%ld %d is eating\n"RESET, timestamp, table->philosopher);
	pthread_mutex_unlock(&table->print_mutex);
}

void	prepare_to_sleep(t_thg *table)
{
	pthread_mutex_lock(&table->fork_mutex);
	table->fork = 0;
	table->prev->fork = 0;
	pthread_mutex_unlock(&table->fork_mutex);
	table->eating = false;
	table->sleeping = true;
}

void	philo_sleep(t_thg *table, long timestamp)
{
	pthread_mutex_lock(&table->print_mutex);
	printf(BLUE"%ld %d is sleeping\n"RESET, timestamp + table->t_t_eat, table->philosopher);
	pthread_mutex_unlock(&table->print_mutex);
}

void	philo_think(t_thg *table, long timestamp)
{
	table->sleeping = false;
	table->thinking = true;
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d is thinking\n", timestamp + table->t_t_sleep + table->t_t_eat, table->philosopher);
	pthread_mutex_unlock(&table->print_mutex);
	table->thinking = false;
}
