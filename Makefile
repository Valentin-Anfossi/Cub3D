# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vagabundo <vagabundo@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2025/09/12 00:53:02 by vagabundo        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBFT	= ./libft/libft.a

SRCS	= ./srcs/*.c

MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	gcc -g -Wall -Wextra -Werror -fsanitize=address $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx-linux

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean
	
# @make -C ./minilibx-linux fclean

re: fclean all