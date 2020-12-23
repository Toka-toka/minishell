# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: white <white@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/14 17:29:46 by sedric            #+#    #+#              #
#    Updated: 2020/11/15 03:25:05 by white            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC = 	src/main.c\
		src/parsing_input.c\
		src/color_start.c\
		src/run_manager.c\
		src/check_way.c\
		src/fork_create.c\
		src/launch.c\
		src/our_command/echo_exit.c\
		src/our_command/export.c\
		src/our_command/pwd_cd.c\
		src/our_command/unset_env.c

OBJ = $(SRC:.c=.o)

LIBFT = libft.a

HEADER = includes/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	mv libft/$(LIBFT) .
	gcc $(FLAGS) -g -o $(NAME) $(SRC) $(LIBFT)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft.a

re: fclean all

bonus: all

.PHONY: all clean fclean re
