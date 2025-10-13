# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2025/10/12 10:39:48 by vanfossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBFT	= ./libft/libft.a

SRCS	= ./srcs/*.c

MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	cc -g -Wall -Wextra -Werror $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx-linux

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean
	
# @make -C ./minilibx-linux fclean

gprof : $(SRCS) $(LIBFT)
	gcc -pg -Wall -Wextra -Werror $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

re: fclean all