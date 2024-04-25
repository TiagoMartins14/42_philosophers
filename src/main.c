/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:57:55 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/25 12:27:59 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_thg	thg;
	
	if (argc == 5 || argc == 6)
	{
		check_and_parse_input(thg, argv);
		assemble_the_hunger_games(argc, argv);
		start_the_hunger_games(argc, argv);
	}
	else
		printf("Invalid input! Valid arguments: "
		"<NUM_OF_PHILOS> <T_T_DIE> <T_T_EAT> <T_T_SLEEP> [MAX_MEALS]\n");
	return (0);
}
