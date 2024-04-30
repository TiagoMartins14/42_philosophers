/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/29 20:55:25 by tiaferna         ###   ########.fr       */
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
# include <errno.h>

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define FAINT "\033[2m"
# define ITALIC "\033[3m"
# define ULINE "\033[4m"
# define SBLINK "\033[5m"
# define FBLINK "\033[6m"
# define REVCOL "\033[7m"
# define HIDDEN "\033[8m"
# define CROSS "\033[9m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef pthread_mutex_t	t_mtx;
typedef struct	s_thg t_thg;

typedef enum e_char_type
{
	SPACE,
	DIGIT,
}	t_char_type;

typedef	enum e_op
{
	INIT,
	CREATE,
	DESTROY,
	JOIN,
	DETACH,
	LOCK,
	UNLOCK,
}	t_op;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DEAD,
}	t_philo_status;

typedef struct s_forks
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	bool		full;
	long		meals_counter;
	long		last_meal_time;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_mtx		philo_mutex;
	t_thg		*thg;
}	t_philo;

// thg stands for "The Hunger Games"
struct s_thg
{
	long		t_t_die;
	long		t_t_eat;
	long		t_t_sleep;
	long		max_meals;
	long		philo_nbr;
	long		numof_running_threads;
	long		start_time;
	bool		thg_finished;
	bool		all_ready;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	checker;
	t_mtx		game_mutex;
	t_mtx		print_mutex;
}	;


// actions.c
void	print_action(t_philo_status status, t_philo *philo);
void	philo_eat(t_philo *philo);

// ft_utils.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);

// input_parser.c
long	check_and_parse_input(t_thg *game, char **argv);

// malloc_utils.c
void	*handle_malloc(size_t bytes);

// mem_free.c
void	free_the_games(t_thg *thg);

// mutex_utils.c
long	mutex_handle(t_mtx *mutex, t_op operation);

// setters_and_getters.c
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
bool	game_over_condition_met(t_thg *thg);

// structs_init.c
void	t_philo_init(t_thg *game);
long	assemble_the_hunger_games(t_thg *game);

// the_hunger_games_utils.c
void	give_out_forks(t_philo *philo, t_fork *forks, int philo_pos);
void	odds_go_first(t_philo *philo);

// the_hunger_games.c
void	*fight(void *args);
void	*big_brother(void *args);
long	start_the_hunger_games(t_thg *game);

// threads_utils.c
long	thread_handle(pthread_t *thread, void *(*foo)(void *), \
										void *data, t_op operation);
bool	all_threads_started(t_mtx *mutex, long *threads, long philo_nbr);
void	wait_all_threads_ready(t_thg *thg);
void	add_to_numof_running_threads(t_mtx *mutex, long *num);

// time.c
void	ft_usleep(long usec, t_thg *table);
long	get_time_in_ms(void);

#endif