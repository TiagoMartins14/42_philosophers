# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 10:24:33 by tiaferna          #+#    #+#              #
#    Updated: 2024/05/02 12:37:14 by tiaferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RESET	= \033[0m
BOLD	= \033[1m
FAINT	= \033[2m
ITALIC	= \033[3m
ULINE	= \033[4m
SBLINK	= \033[5m
FBLINK	= \033[6m
REVCOL	= \033[7m
HIDDEN	= \033[8m
CROSS	= \033[9m
BLACK   = \033[1;30m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
PURPLE  = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

OBJS_DIR		= objs

INCLUDES		= philosophers.h

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -fsanitize=thread
RM				= rm -rf

SRCS			= 	actions.c \
					ft_utils.c \
					input_parser.c \
					main.c \
					malloc_utils.c \
					mem_free.c \
					mutex_utils.c \
					setters_and_getters.c \
					structs_init.c \
					the_hunger_games_utils.c \
					the_hunger_games.c \
					threads_utils.c \
					time.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

#default target
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)./philo executable is ready!$(RESET)"

#create .o fies
# $< first prerequisite aka .c; $@ output/target file aka .o
$(OBJS_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -I $(CFLAGS) -c $< -o $@

#testing fd leaks
leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./philo

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	@echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	$(RM) $(NAME)

#reset environment - remove everything and recompile
re: fclean
	$(MAKE) all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
.SILENT:
