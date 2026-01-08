# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2026/01/08 18:36:39 by vanfossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= cub3D

LIBFT	= ./libft/libft.a

SRCS	= 	./srcs/check_map.c ./srcs/check_map2.c ./srcs/clean.c \
			./srcs/colors_utils.c ./srcs/debug.c ./srcs/draw_background.c \
			./srcs/draw_ray.c ./srcs/draw_utils.c ./srcs/draw_vertical.c \
			./srcs/draw_walls.c ./srcs/drawer.c ./srcs/errors.c \
			./srcs/ft_memcpyfast.c ./srcs/handle_keys.c ./srcs/img.c \
			./srcs/init.c ./srcs/init2.c ./srcs/init3.c ./srcs/main.c \
			./srcs/map_utils.c ./srcs/map.c ./srcs/movement.c \
			./srcs/parseutils.c ./srcs/file_check.c ./srcs/map_check.c \
			./srcs/map_check2.c ./srcs/check_mapstr.c ./srcs/check_player.c \
			./srcs/map_init.c \
			./srcs/bonus.c ./srcs/bonus2.c ./srcs/bonus3.c

SRCS_BONUS = 


MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

bonus : $(BONUS)

$(BONUS): $(SRCS_BONUS) $(MLX) $(LIBFT)
	cc -g -Wall -Wextra -Werror $(SRCS_BONUS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(NAME): $(SRCS) $(MLX) $(LIBFT)
	cc -g -Wall -Wextra -Werror $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx-linux

clean:
	@rm -f $(NAME)
	@make -C ./libft clean
	@make -C ./minilibx-linux clean

fclean: clean
	@make -C ./libft fclean

gprof : $(SRCS) $(LIBFT)
	gcc -pg -Wall -Wextra -Werror $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

re: fclean all



