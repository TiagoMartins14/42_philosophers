/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:06:35 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 09:15:36 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_the_games(t_thg *table)
{
	t_thg *temp;

	table->prev->next = NULL;
	while (table)
	{
		temp = table;
		table->t_t_die = 0;
		table->t_t_eat = 0;
		table->t_t_sleep = 0;
		table->max_meals = 0;
		table->meals_counter = 0;
		table->philosopher = 0;
		table->fork = 0;
		table->current_time = 0;
		table->last_meal = 0;
		*table->start_time = 0;
		table->eating = false;
		table->sleeping = false;
		table->thinking = false;
		*table->dead = false;
		table = table->next;
		free(temp);
	}
}
