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
CCFLAGS	= -Wextra -Werror -Wall -g3

NAME =	so_long
SRC =	src/main.c \
		src/move.c \
		src/validate_map.c \
		src/validate_object.c \
		src/charge_map.c \
		src/validate_conections.c \
		src/charge_sprite.c \
		src/draw_map.c \
		src/errors.c \

OBJ = $(SRC:.c=.o)

INCLUDE = libft/libft.h src/so_long.h


$(NAME): $(OBJ) $(INCLUDE)
	$(MAKE) -C libft/
	$(CC) $(CCFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit libft/libft.a -o $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -Imlx -c $< -o $@

clean:
	$(MAKE) -C libft/ clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
