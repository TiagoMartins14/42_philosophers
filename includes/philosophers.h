/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiago             #+#    #+#             */
/*   Updated: 2024/03/20 11:45:15 by tiago            ###   ########.fr       */
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

#endif