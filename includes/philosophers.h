/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 09:48:25 by tiaferna         ###   ########.fr       */
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

typedef struct s_thg
{
	int				t_t_die;
	int				t_t_eat;
	int				t_t_sleep;
	int				max_meals;
	int				meals_counter;
	int				philosopher;
	int				fork;
	long			current_time;
	long			last_meal;
	long			*start_time;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	bool			*dead;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	struct s_thg	*next;
	struct s_thg	*prev;
}	t_thg;

// actions.c
void	philo_eat(t_thg *table, long timestamp);
void	prepare_to_sleep(t_thg *table);
void	philo_sleep(t_thg *table, long timestamp);
void	philo_think(t_thg *table, long timestamp);

// conditions.c
bool	has_two_forks(t_thg *table);
bool	is_dead(t_thg *table, long timestamp);
bool	death_checker(t_thg *table);
bool	grim_reaper_arrived(t_thg *table, long elapsed_usec);

// ft_utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *nstr);

// mem_free.c
void	free_the_games(t_thg *table);

// structs_init.c
void	t_thg_common_var_setter(t_thg *game, long *set_start, bool *death);
void	t_thg_init(t_thg *game, int i, char **argv);

// time.c
int		ft_usleep(int usec, t_thg *table);
long	get_time(void);
long	timestamp_calc(long current_time, long start_time);

#endif