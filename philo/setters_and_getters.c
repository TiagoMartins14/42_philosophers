/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_and_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:22:12 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/14 13:07:44 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handle(mutex, LOCK);
	*dest = value;
	mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handle(mutex, LOCK);
	ret = *value;
	mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	game_over_condition_met(t_thg *thg)
{
	return (get_bool(&thg->game_mutex, &thg->thg_finished));
}
