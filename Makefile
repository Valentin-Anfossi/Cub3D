# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2026/01/26 13:30:38 by vanfossi         ###   ########.fr        #
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

OBJS    =	$(SRCS:.c=.o)

SRCS_BONUS  = bonus2_bonus.c bonus3_bonus.c bonus_bonus.c check_map2_bonus.c \
	check_map_bonus.c check_mapstr_bonus.c check_player_bonus.c clean_bonus.c \
	colors_utils_bonus.c cub3d_bonus.h debug_bonus.c draw_background_bonus.c drawer_bonus.c \
	draw_ray_bonus.c draw_utils_bonus.c draw_vertical_bonus.c draw_walls_bonus.c \
	errors_bonus.c file_check_bonus.c ft_memcpyfast_bonus.c handle_keys_bonus.c \
	img_bonus.c init2_bonus.c init3_bonus.c init_bonus.c main_bonus.c map_bonus.c \
	map_check2_bonus.c map_check_bonus.c map_init_bonus.c map_utils_bonus.c \
    movement_bonus.c note parseutils_bonus.c


OBJS_BONUS = $(SRCS_BONUS:.c=.o)

MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

bonus: $(OBJS_BONUS) $(MLX) $(LIBFT)
	cc -g -Wall -Wextra -Werror $(SRCS_BONUS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	cc -g -Wall -Wextra -Werror $(SRCS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx-linux

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@make -C ./libft clean
	@make -C ./minilibx-linux clean

fclean: clean
	@make -C ./libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re