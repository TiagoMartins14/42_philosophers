/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:37:44 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/30 20:09:22 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time_in_ms() - philo->thg->start_time;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	mutex_handle(&philo->thg->print_mutex, LOCK);
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) && \
	!game_over_condition_met(philo->thg))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !game_over_condition_met(philo->thg))
		printf(GREEN"%ld %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !game_over_condition_met(philo->thg))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !game_over_condition_met(philo->thg))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf(RED"%ld %d died\n"RESET, elapsed, philo->id);
	mutex_handle(&philo->thg->print_mutex, UNLOCK);
}

void	philo_eat(t_philo *philo)
{
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_action(TAKE_RIGHT_FORK, philo);
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_action(TAKE_LEFT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	philo->meals_counter++;
	print_action(EATING, philo);
	ft_usleep(philo->thg->t_t_eat, philo->thg);
	if (philo->thg->max_meals > 0 && \
	philo->meals_counter == philo->thg->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
}
