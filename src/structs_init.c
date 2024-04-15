/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:33:39 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/15 17:02:27 by tiaferna         ###   ########.fr       */
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
	printf("a\n");
	game->meals_counter = malloc(sizeof(int));
	*game->meals_counter = 0;
	printf("b\n");
	game->start_time = malloc(sizeof(int));
	*game->start_time = -1;
	printf("c\n");
	game->dead = malloc(sizeof(bool));
	*game->dead = false;
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
