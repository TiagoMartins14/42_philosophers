/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:27:16 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/24 14:03:33 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	handle_thread_error(int status, t_op operation)
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

int	thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_op operation)
{
	int	status;

	if (operation == CREATE)
		status = handle_thread_error(pthread_create(thread, NULL, foo, data), operation);
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
