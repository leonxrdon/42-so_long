# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 18:18:41 by lnarvaez          #+#    #+#              #
#    Updated: 2023/07/12 18:18:49 by lnarvaez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM	= rm -f
CC	= gcc
CCFLAGS	= -Wextra -Werror -Wall

NAME = so_long
SRC = main.c move.c gnl/get_next_line.c gnl/get_next_line_utils.c \
	libft/ft_split.c\

OBJ = $(SRC:.c=.o)

INCLUDE = gnl/get_next_line.h libft/libft.h so_long.h

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
