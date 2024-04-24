/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/24 15:04:29 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	t_thg_init(t_thg *game, t_thg *chair, int i, char **argv)
{
	chair->t_t_die = ft_atoi(argv[2]);
	chair->t_t_eat = ft_atoi(argv[3]);
	chair->t_t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		chair->max_meals = ft_atoi(argv[5]);
	else
		chair->max_meals = -1;
	chair->meals_counter = game->meals_counter;
	chair->start_time = game->start_time;
	chair->dead = game->dead;
	chair->philosopher = i;
	chair->fork = 0;
	chair->current_time = 0;
	chair->last_meal = 0;
	chair->eating = false;
	chair->sleeping = false;
	chair->thinking = false;
	chair->fork_mutex = malloc(sizeof(t_mtx));
	mutex_handle(chair->fork_mutex, INIT);
	chair->dead_mutex = malloc(sizeof(t_mtx));
	mutex_handle(chair->dead_mutex, INIT);
	chair->time_mutex = malloc(sizeof(t_mtx));
	mutex_handle(chair->time_mutex, INIT);
	chair->next = NULL;
	chair->prev = NULL;
}

void	t_thg_first_init(t_thg *game, int i, char **argv)
{
	game->t_t_die = ft_atoi(argv[2]);
	game->t_t_eat = ft_atoi(argv[3]);
	game->t_t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		game->max_meals = ft_atoi(argv[5]);
	else
		game->max_meals = -1;
	game->meals_counter = malloc(sizeof(int));
	*game->meals_counter = 0;
	game->start_time = malloc(sizeof(int));
	*game->start_time = -1;
	game->dead = malloc(sizeof(bool));
	*game->dead = false;
	game->philosopher = i;
	game->fork = 0;
	game->current_time = 0;
	game->last_meal = 0;
	game->eating = false;
	game->sleeping = false;
	game->thinking = false;
	game->fork_mutex = malloc(sizeof(t_mtx));
	mutex_handle(game->fork_mutex, INIT);
	game->dead_mutex = malloc(sizeof(t_mtx));
	mutex_handle(game->dead_mutex, INIT);
	game->time_mutex = malloc(sizeof(t_mtx));
	mutex_handle(game->time_mutex, INIT);
	game->next = NULL;
	game->prev = NULL;
}
