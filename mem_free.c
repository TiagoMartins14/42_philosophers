/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:06:35 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/02 12:32:07 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_the_games(t_thg *thg)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < thg->philo_nbr)
	{
		philo = thg->philos + 1;
		if (thg->philo_nbr != 1)
			mutex_handle(&philo->philo_mutex, DESTROY);
	}
	mutex_handle(&thg->game_mutex, DESTROY);
	mutex_handle(&thg->print_mutex, DESTROY);
	free(thg->forks);
	free(thg->philos);
}
