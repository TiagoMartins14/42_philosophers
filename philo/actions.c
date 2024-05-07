/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:37:44 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/07 12:25:29 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_fork_action(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	mutex_handle(&philo->thg->print_mutex, LOCK);
	elapsed = get_time_in_ms() - philo->thg->start_time;
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) && \
	!game_over_condition_met(philo->thg))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
}

void	print_eating(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	mutex_handle(&philo->thg->print_mutex, LOCK);
	elapsed = get_time_in_ms() - philo->thg->start_time;
	if (!game_over_condition_met(philo->thg))
		printf("%ld %d is eating\n", elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
}

void	print_sleeping(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	mutex_handle(&philo->thg->print_mutex, LOCK);
	elapsed = get_time_in_ms() - philo->thg->start_time;
	if (!game_over_condition_met(philo->thg))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
}

void	print_thinking(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	mutex_handle(&philo->thg->print_mutex, LOCK);
	elapsed = get_time_in_ms() - philo->thg->start_time;
	if (!game_over_condition_met(philo->thg))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
	if (philo->thg->philo_nbr % 2)
		usleep(500);
}

void	print_dead(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	if (philo->thg->philo_nbr == 1)
		usleep(philo->thg->t_t_die);
	mutex_handle(&philo->thg->print_mutex, LOCK);
	elapsed = get_time_in_ms() - philo->thg->start_time;
	printf("%ld %d died\n", elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
}
