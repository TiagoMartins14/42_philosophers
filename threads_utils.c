/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:27:16 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/02 12:32:33 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	handle_thread_error(int status, t_op operation)
{
	if (status == EAGAIN)
		printf("No ressources to create abother thread.\n");
	else if (status == EPERM)
		printf("The caller does not have appropriate permission.\n");
	else if (status == EINVAL && operation == CREATE)
		printf("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (operation == JOIN || operation == DETACH))
		printf("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		printf("No thread could be found corresponding to that specified"
			" by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		printf("A deadlock was detected or the value of thread"
			"specifies the calling thread.\n");
	return (status);
}

long	thread_handle(pthread_t *thread, void *(*foo)(void *), \
									void *data, t_op operation)
{
	int	status;

	if (operation == CREATE)
		status = handle_thread_error(pthread_create(thread, NULL, \
		foo, data), operation);
	else if (operation == JOIN)
		status = handle_thread_error(pthread_join(*thread, NULL), operation);
	else if (operation == DETACH)
		status = handle_thread_error(pthread_detach(*thread), operation);
	else
	{
		printf("Wrong operation value for thread_handle:"
			" use <CREATE> <JOIN> <DETACH>");
		status = -1;
	}
	return (status);
}

bool	all_threads_started(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	status;

	status = false;
	mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		status = true;
	mutex_handle(mutex, UNLOCK);
	return (status);
}

void	wait_all_threads_ready(t_thg *thg)
{
	while (!get_bool(&thg->game_mutex, &thg->all_ready))
		;
}

void	add_to_numof_running_threads(t_mtx *mutex, long *num)
{
	mutex_handle(mutex, LOCK);
	(*num)++;
	mutex_handle(mutex, UNLOCK);
}
