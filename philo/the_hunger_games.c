/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_hunger_thgs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:51:28 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/29 21:25:31 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*fight(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	wait_all_threads_ready(philo->thg);
	odds_go_first(philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	add_to_numof_running_threads(&philo->thg->game_mutex, \
	&philo->thg->numof_running_threads);
	while (!game_over_condition_met(philo->thg))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		philo_eat(philo);
		print_sleeping(philo);
		ft_usleep(philo->thg->t_t_sleep, philo->thg);
		print_thinking(philo);
	}
	return (NULL);
}

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_t_die;
	long	last_meal_time;

	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = 0;
	t_t_die = philo->thg->t_t_die / 1e3;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time_in_ms() - last_meal_time;	
	if (elapsed > t_t_die)
		return (true);
	return (false);
}

void	*big_brother(void *args)
{
	int		i;
	t_thg	*thg;

	thg = (t_thg *)args;
	while (!all_threads_started(&thg->game_mutex, \
	&thg->numof_running_threads, thg->philo_nbr))
		;
	while (!game_over_condition_met(thg))
	{
		i = -1;
		while (++i < thg->philo_nbr && !game_over_condition_met(thg))
		{
			if (philo_died(thg->philos + i))
			{
				set_bool(&thg->game_mutex, &thg->thg_finished, true);
				print_dead(thg->philos + i);
			}
		}
	}
	return (NULL);
}

long	start_the_hunger_games(t_thg *thg)
{
	int	i;

	i = -1;
	if (thg->max_meals == 0)
		return (0);
	else if (thg->philo_nbr == 1)
		thread_handle(&thg->philos[0].thread_id, process_single_philo,
			&thg->philos[0], CREATE);
	else
		while (++i < thg->philo_nbr)
			thread_handle(&thg->philos[i].thread_id, fight,
				&thg->philos[i], CREATE);
	thread_handle(&thg->checker, big_brother, thg, CREATE);
	thg->start_time = get_time_in_ms();
	set_bool(&thg->game_mutex, &thg->all_ready, true);
	i = -1;
	while (++i < thg->philo_nbr)
		thread_handle(&thg->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&thg->game_mutex, &thg->thg_finished, true);
	thread_handle(&thg->checker, NULL, NULL, JOIN);
	return (0);
}
