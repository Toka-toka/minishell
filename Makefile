# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: white <white@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/14 17:29:46 by sedric            #+#    #+#              #
#    Updated: 2020/11/11 22:31:30 by white            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC = 	src/main.c\
		src/envp.c\


OBJ = $(SRC:.c=.o)

LIBFT = libft.a

HEADER = includes/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	mv libft/$(LIBFT) .
	gcc $(FLAGS) -g -o $(NAME) $(SRC) $(LIBFT) $(HEADER)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft.a

re: fclean all

bonus: all

.PHONY: all clean fclean re