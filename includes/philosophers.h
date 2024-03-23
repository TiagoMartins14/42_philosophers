/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiago             #+#    #+#             */
/*   Updated: 2024/03/23 23:09:43 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_events
{
	int				argv_1;
	int				argv_2;
	int				argv_3;
	int				argv_4;
	int				argv_5;
	int				philosopher;
	int				fork;
	int				priority;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	bool			dead;
	struct timeval	start_time;
	struct timeval	current_time;
	struct s_events	*next;
	struct s_events	*prev;
}	t_events;

// utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *nstr);

#endif