/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/02 12:32:22 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	t_philo_init(t_thg *thg)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < thg->philo_nbr)
	{
		philo = thg->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		mutex_handle(&philo->philo_mutex, INIT);
		philo->thg = thg;
		give_out_forks(philo, thg->forks, i);
	}
}

long	assemble_the_hunger_games(t_thg *thg)
{
	int	i;

	i = -1;
	thg->numof_running_threads = 0;
	thg->thg_finished = false;
	thg->all_ready = false;
	thg->philos = handle_malloc(sizeof(t_philo) * thg->philo_nbr);
	if (!thg->philos)
		return (-1);
	thg->forks = handle_malloc(sizeof(t_fork) * thg->philo_nbr);
	if (!thg->forks)
		return (-1);
	mutex_handle(&thg->game_mutex, INIT);
	mutex_handle(&thg->print_mutex, INIT);
	while (++i < thg->philo_nbr)
	{
		mutex_handle(&thg->forks[i].fork, INIT);
		thg->forks[i].fork_id = i;
	}
	t_philo_init(thg);
	return (0);
}
