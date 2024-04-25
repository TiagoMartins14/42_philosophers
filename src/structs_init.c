/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/25 12:28:50 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_and_parse_input(thg, argv)
{
	
}

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

void	t_philo_init(t_thg *game)
{
	int	i;
	t_philo *philo;
	
	i = -1;
	while (++i < game->philo_nbr)
	{
		philo = game->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		mutex_handle(&philo->philo_mutex, INIT);
		philo->thg = game;
		give_out_forks(philo, game->forks, i);
	}
}

int	t_thg_init(t_thg *game, char **argv)
{
	int	i;

	i = -1;
	game->numof_running_threads = 0;
	game->thg_finished = false;
	game->all_ready = false;
	game->philos = handle_malloc(sizeof(t_philo) * game->philo_nbr);
	if (!game->philos)
		return (-1);
	game->forks = handle_malloc(sizeof(t_fork) * game->philo_nbr);
	if (!game->forks)
		return (-1);
	mutex_handle(game->table_mutex, INIT);
	mutex_handle(game->print_mutex, INIT);
	while (++i < game->philo_nbr)
	{
		mutex_handle(&game->forks[i].fork, INIT);
		game->forks[i].fork_id = i;
	}
	t_philo_init(game);
}
