# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpierce <mpierce@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 11:48:41 by mpierce           #+#    #+#              #
#    Updated: 2025/01/31 12:30:12 by mpierce          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SOURCES = \
			srcs/pipex.c \
			srcs/pipex_utils.c \
			srcs/piping.c \
			srcs/piping_utils.c \
			srcs/handle_files.c \
			srcs/handle_heredoc.c

LIBFT_PATH = ./libftmaster

LIBFT = $(LIBFT_PATH)/libft.a

OBJECTS = $(SOURCES:.c=.o)

GREEN = \e[1;32m
PURPLE = \e[1;35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN) \npipex Compiled\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@$(RM) $(OBJECTS)
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@echo "$(GREEN)\nObjects Cleaned\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@$(RM) $(NAME)
	@echo "$(GREEN)\nExecutable Clean Complete\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"

re: fclean all

full: fclean all
	@$(RM) $(OBJECTS)
	@echo "$(GREEN)\nObjects Cleaned\n$(RESET)"
	@echo "$(PURPLE)------------------------------------$(RESET)"
	@make -C $(LIBFT_PATH) clean --no-print-directory

good: all clean

.PHONY: all clean fclean re libft full good