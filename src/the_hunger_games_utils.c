/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_hunger_games_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:28:57 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/02 08:09:22 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		usleep(60);
}
