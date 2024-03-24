/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiago             #+#    #+#             */
/*   Updated: 2024/03/24 12:35:58 by tiago            ###   ########.fr       */
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

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define FAINT "\033[2m"
#define ITALIC "\033[3m"
#define ULINE "\033[4m"
#define SBLINK "\033[5m"
#define FBLINK "\033[6m"
#define REVCOL "\033[7m"
#define HIDDEN "\033[8m"
#define CROSS "\033[9m"
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

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
	long			start_time;
	long			current_time;
	long			last_meal;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	bool			dead;
	struct s_events	*next;
	struct s_events	*prev;
}	t_events;

// utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *nstr);

#endif