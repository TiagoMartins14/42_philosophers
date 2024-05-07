/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_hunger_games_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:28:57 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/07 12:24:24 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	give_out_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	if (philo->id % 2 != 0)
	{
		philo->left_fork = &forks[(philo_pos + 1) % philo->thg->philo_nbr];
		philo->right_fork = &forks[philo_pos];
	}
	else
	{
		philo->left_fork = &forks[philo_pos];
		philo->right_fork = &forks[(philo_pos + 1) % philo->thg->philo_nbr];
	}
}

void	odds_go_first(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(4200, philo->thg);
}

void	think_action(t_philo *philo, bool sim_started)
{
	long	tt_eat;
	long	tt_sleep;
	long	tt_think;

	if (sim_started)
		print_thinking(philo);
	if (philo->thg->philo_nbr % 2 == 0)
		return ;
	else
	{
		tt_eat = philo->thg->t_t_eat;
		tt_sleep = philo->thg->t_t_sleep;
		tt_think = (tt_eat * 2) - tt_sleep;
		if (tt_think < 0)
			tt_think = 0;
		ft_usleep(tt_think * 1e3 * 0.5, philo->thg);
	}
}

void	*process_single_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->thg->start_time = get_time_in_ms();
	add_to_numof_running_threads(&philo->thg->game_mutex, \
		&philo->thg->numof_running_threads);
	print_fork_action(TAKE_RIGHT_FORK, philo);
	ft_usleep(philo->thg->t_t_die * 1e3, philo->thg);
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	mutex_handle(&philo->right_fork->fork, LOCK);
	print_fork_action(TAKE_RIGHT_FORK, philo);
	mutex_handle(&philo->left_fork->fork, LOCK);
	print_fork_action(TAKE_LEFT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	philo->meals_counter++;
	print_eating(philo);
	ft_usleep(philo->thg->t_t_eat, philo->thg);
	if (philo->thg->max_meals > 0 && \
	philo->meals_counter == philo->thg->max_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handle(&philo->right_fork->fork, UNLOCK);
	mutex_handle(&philo->left_fork->fork, UNLOCK);
}
