/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiago             #+#    #+#             */
/*   Updated: 2024/03/20 18:51:52 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_events
{
	int				philosopher;
	int				fork;
	int				priority;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	char			**argv;
	struct s_events	*next;
	struct s_events	*prev;
}	t_events;

typedef struct s_thread_args
{
	t_events	*table_node;
	char		**argv;
} t_thread_args;

// utils.c
static char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *str);
int	ft_atoi(const char *nstr);

#endif