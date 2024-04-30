/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:43:11 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/29 21:09:34 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	is_type(char c, t_char_type type)
{
	if (type == SPACE)
		return ((c >= 9 && c <= 13) || 32 == c);
	else if (type == DIGIT)
		return (c >= '0' && c <= '9');
	else
		printf("Invalid char type inserted in function is_type().\n");
	return (false);
}

static long	check_input(const char *str)
{
	int			len;

	len = 0;
	while (is_type(*str, SPACE))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-' || !is_type(*str, DIGIT))
	{
		if (*str == '-')
			printf(RED"Please insert only positive numbers.\n"RESET);
		else
			printf(RED"The input is not a digit"RESET);
		return (-1);
	}
	while (is_type(*str++, DIGIT))
		++len;
	if (len > 10)
	{
		printf(RED"The number cannot be bigger "
		"than 2147483647 (INT_MAX).\n"RESET);
		return (-1);
	}
	return (0);
}

static const char	*get_num(const char *str)
{
	int			len;
	const char	*num;

	len = 0;
	if (check_input(str) == -1)
		return (NULL);
	while (is_type(*str, SPACE))
		++str;
	if (*str == '+')
		++str;
	num = str;
	while (is_type(*str++, DIGIT))
		++len;
	return (num);
}

static long	ft_atol(const char *nstr)
{
	long	nb;

	nb = 0;
	nstr = get_num(nstr);
	if (nstr == NULL)
		return (-1);
	while (is_type(*nstr, DIGIT))
		nb = (nb * 10) + (*nstr++ - '0');
	if (nb > __INT_MAX__)
	{
		printf(RED"The number cannot be bigger than"
		" 2147483647 (INT_MAX).\n"RESET);
		return (-1);
	}
	return (nb);
}

long	check_and_parse_input(t_thg *thg, char **argv)
{
	thg->philo_nbr = ft_atol(argv[1]);
	if (thg->philo_nbr > PHILO_MAX)
	{
		printf(RED"The maximum number of philosophers "
		"allowed is %d\n", PHILO_MAX);
		return (-1);
	}
	thg->t_t_die = ft_atol(argv[2]) * 1e3;
	thg->t_t_eat = ft_atol(argv[3]) * 1e3;
	thg->t_t_sleep = ft_atol(argv[4]) * 1e3;
	if (thg->t_t_die < 6e4
		|| thg->t_t_sleep < 6e4
		|| thg->t_t_eat < 6e4)
	{
		printf(RED"Timestamps need to be bigger than 60ms\n"RESET);
		return (-1);
	}
	if (argv[5])
		thg->max_meals = ft_atol(argv[5]);
	else
		thg->max_meals = -1;
	return (0);
}
