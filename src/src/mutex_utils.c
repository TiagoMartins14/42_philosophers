/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:36:30 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/29 20:41:53 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static long handle_mtx_error(int status, t_op operation)
{
	if (status == EINVAL && (operation == LOCK || operation == UNLOCK || operation == DESTROY))
		printf("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && operation == INIT)
		printf("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		printf("A deadlock would occur if the thread blocked waiting for mutex.\n");
	else if (status == EPERM)
		printf("The current thread does not hold a lock on the mutex.\n");
	else if (status == ENOMEM)
		printf("The process cannot allocate enough memory to create another mutex.\n");
	else if (status == EBUSY)
		printf("Mutex is locked.\n");
	return (status);
}

long	mutex_handle(t_mtx *mutex, t_op operation)
{
	int	status;

	if (operation == LOCK)
		status = handle_mtx_error(pthread_mutex_lock(mutex), operation);
	else if (operation == UNLOCK)
		status = handle_mtx_error(pthread_mutex_unlock(mutex), operation);
	else if (operation == INIT)
		status = handle_mtx_error(pthread_mutex_init(mutex, NULL), operation);
	else if (operation == DESTROY)
		status = handle_mtx_error(pthread_mutex_destroy(mutex), operation);
	else
	{
		printf("Wrong operation value for mutex handle.\n");
		status = -1;
	}
	return (status);
}
