/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/26 18:22:14 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	t_thg_common_var_setter(t_thg *game, long *set_start, bool *death)
{
	game->start_time = set_start;
	game->dead = death;
}

void	t_thg_init(t_thg *game, int i, char **argv)
{
	game->t_t_die = ft_atoi(argv[2]);
	game->t_t_eat = ft_atoi(argv[3]);
	game->t_t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		game->max_meals = ft_atoi(argv[5]);
	else
		game->max_meals = -1;
	game->meals_counter = 0;
	game->philosopher = i;
	game->fork = 0;
	game->current_time = 0;
	game->last_meal = 0;
	game->eating = false;
	game->sleeping = false;
	game->thinking = false;
	game->next = NULL;
	game->prev = NULL;
}
