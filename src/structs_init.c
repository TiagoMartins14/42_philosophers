/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/26 14:32:05 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	t_thg_init(t_thg *game, int i, long *set_start, char **argv)
{
	game->argv_1 = ft_atoi(argv[1]);
	game->argv_2 = ft_atoi(argv[2]);
	game->argv_3 = ft_atoi(argv[3]);
	game->argv_4 = ft_atoi(argv[4]);
	if (argv[5])
		game->argv_5 = ft_atoi(argv[5]);
	else
		game->argv_5 = -1;
	game->meals = 0;
	game->philosopher = i;
	game->fork = 0;
	game->priority = i;
	game->current_time = 0;
	game->last_meal = 0;
	game->start_time = set_start;
	game->all_set = false;
	game->eating = false;
	game->sleeping = false;
	game->thinking = false;
	game->dead = false;
	game->next = NULL;
	game->prev = NULL;
}
