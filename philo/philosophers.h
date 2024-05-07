/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:24:33 by tiaferna          #+#    #+#             */
/*   Updated: 2024/05/07 12:13:01 by tiaferna         ###   ########.fr       */
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
typedef struct s_thg	t_thg;

typedef enum e_char_type
{
	SPACE,
	DIGIT,
}	t_char_type;

typedef enum e_op
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

/*
 * actions.c
*/
/// @brief Prints the philosopher's fork taking action on the terminal
/// @param status 
/// @param philo
void	print_fork_action(t_philo_status status, t_philo *philo);

/// @brief Prints the philosopher's eating action on the terminal
/// @param philo 
void	print_eating(t_philo *philo);

/// @brief Prints the philosopher's sleeping action on the terminal
/// @param philo 
void	print_sleeping(t_philo *philo);

/// @brief Prints the philosopher's thinking action on the terminal
/// @param philo 
void	print_thinking(t_philo *philo);

/// @brief Prints the philosopher's dead action on the terminal
/// @param philo 
void	print_dead(t_philo *philo);

/*
 * ft_utils.c
*/
/// @brief Returns the length of a string
/// @param s
/// @return size_t
size_t	ft_strlen(const char *s);

/// @brief Returns a pointer to a duplicate of a string
/// @param str 
/// @return char *
char	*ft_strdup(const char *str);

/// @brief Compares strings 's1' and 's2' character by character.
/// @param s1 
/// @param s2 
/// @return If the strings are equal, the function returns 0.
int		ft_strcmp(char *s1, char *s2);

/*
 * input_parser.c
*/
/// @brief Parses the input and then checks its validity.
/// @brief Returns -1 if invalid input is found
/// @param game 
/// @param argv 
/// @return long
long	check_and_parse_input(t_thg *game, char **argv);

/*
 * malloc_utils.c
*/
/// @brief A malloc function that automatically deals with
/// @brief errors it might encounter. 
/// @brief Returns the pointer to the first bite of the allocated memory
/// @param bytes 
/// @return void *
void	*handle_malloc(size_t bytes);

/*
 * mem_free.c
*/
/// @brief Frees all the dinamically allocated memory before closing the program
/// @param thg
void	free_the_games(t_thg *thg);

/*
 * mutex_utils.c
*/
/// @brief A function that wraps all the mutex functions in a single one
/// @brief handling its associated potential errors. If successfull, returns 0
/// @param mutex 
/// @param operation 
/// @return long
long	mutex_handle(t_mtx *mutex, t_op operation);

/*
 * setters_and_getters.c
*/
/// @brief Sets a long int by protecting it with a mutex beforehand
/// @param mutex 
/// @param dest 
/// @param value 
void	set_long(t_mtx *mutex, long *dest, long value);

/// @brief Gets the value of a long int by protecting it with a mutex beforehand
/// @param mutex 
/// @param value 
/// @return long
long	get_long(t_mtx *mutex, long *value);

/// @brief Sets a bool by protecting it with a mutex beforehand
/// @param mutex 
/// @param dest 
/// @param value 
void	set_bool(t_mtx *mutex, bool *dest, bool value);

/// @brief Gets the value of a bool by protecting it with a mutex beforehand
/// @param mutex 
/// @param value 
/// @return bool
bool	get_bool(t_mtx *mutex, bool *value);

/// @brief Checks if the Game Over's condition has been met:
/// @brief a philosopher has died or all the max_meals has been reached
/// @param thg 
/// @return bool
bool	game_over_condition_met(t_thg *thg);

/*
 *structs_init.c
*/
/// @brief Initializes all the structs
/// @param game 
void	t_philo_init(t_thg *game);

/// @brief Gives values to the different struct's parameters
/// @param game 
/// @return long
long	assemble_the_hunger_games(t_thg *game);

/*
 * the_hunger_games_utils.c
*/
/// @brief Assigns forks to each philosopher
/// @param philo 
/// @param forks 
/// @param philo_pos 
void	give_out_forks(t_philo *philo, t_fork *forks, int philo_pos);

/// @brief Allows the odd numbered philos to have a headstart of 60 microseconds
/// @param philo 
void	odds_go_first(t_philo *philo);

/// @brief Special case for a single philo
/// @param args 
/// @return void *
void	*process_single_philo(void *args);

/// @brief Prints the philo's eating status and advances
/// @brief its corresponding time_to_eat
/// @param philo 
void	philo_eat(t_philo *philo);

/*
 * the_hunger_games.c
*/
/// @brief Function responsable for: eat, sleep, think, repeat
/// @param args 
/// @return void *
void	*fight(void *args);

/// @brief Function responsible for monitoring "The Hunger Games"
/// @brief and monitoring the Game Over/Win Condition.
/// @param args 
/// @return void *
void	*big_brother(void *args);

/// @brief Creates each thread and gets the motion going
/// @param game 
/// @return long 
long	start_the_hunger_games(t_thg *game);

/*
 * threads_utils.c
*/

/// @brief Wraps the several thread operations in a single function which also
/// @brief handles the associated errors. if successfull, returns 0
/// @param thread 
/// @param foo 
/// @param data 
/// @param operation 
/// @return long
long	thread_handle(pthread_t *thread, void *(*foo)(void *), \
										void *data, t_op operation);

/// @brief Checks if all the threads have started
/// @param mutex 
/// @param threads 
/// @param philo_nbr 
/// @return bool
bool	all_threads_started(t_mtx *mutex, long *threads, long philo_nbr);

/// @brief Acts as a spinlock waiting for all the threads to be ready
/// @param thg 
void	wait_all_threads_ready(t_thg *thg);

/// @brief A function to increase the value of num_of_running_threads
/// @brief protecting it with a mutex
/// @param mutex 
/// @param num 
void	add_to_numof_running_threads(t_mtx *mutex, long *num);

/*
 * time.c
*/

/// @brief A custom usleep which is more precise than the standard one.
/// @param usec 
/// @param table 
void	ft_usleep(long usec, t_thg *table);

/// @brief Returns the gettimeofday in milliseconds
/// @param  void
/// @return long
long	get_time_in_ms(void);

#endif