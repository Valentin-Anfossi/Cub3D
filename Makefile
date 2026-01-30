# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2026/01/30 05:09:07 by vanfossi         ###   ########.fr        #
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
			./srcs/map_init.c ./srcs/gnl_cleaner.c \

OBJS    =	$(SRCS:.c=.o)

SRCS_BONUS  = 	./srcs_bonus/bonus2_bonus.c ./srcs_bonus/bonus3_bonus.c ./srcs_bonus/bonus_bonus.c \
				./srcs_bonus/check_map2_bonus.c ./srcs_bonus/check_map_bonus.c ./srcs_bonus/check_mapstr_bonus.c \
				./srcs_bonus/check_player_bonus.c ./srcs_bonus/clean_bonus.c ./srcs_bonus/colors_utils_bonus.c \
				./srcs_bonus/debug_bonus.c ./srcs_bonus/draw_background_bonus.c ./srcs_bonus/drawer_bonus.c \
				./srcs_bonus/draw_ray_bonus.c ./srcs_bonus/draw_utils_bonus.c ./srcs_bonus/draw_vertical_bonus.c \
				./srcs_bonus/draw_walls_bonus.c ./srcs_bonus/errors_bonus.c ./srcs_bonus/file_check_bonus.c \
				./srcs_bonus/ft_memcpyfast_bonus.c ./srcs_bonus/handle_keys_bonus.c ./srcs_bonus/img_bonus.c \
				./srcs_bonus/init2_bonus.c ./srcs_bonus/init3_bonus.c ./srcs_bonus/init_bonus.c ./srcs_bonus/main_bonus.c\
				./srcs_bonus/map_bonus.c ./srcs_bonus/map_check2_bonus.c ./srcs_bonus/map_check_bonus.c \
				./srcs_bonus/map_init_bonus.c ./srcs_bonus/map_utils_bonus.c ./srcs_bonus/movement_bonus.c ./srcs_bonus/parseutils_bonus.c \
				./srcs_bonus/gnl_cleaner_bonus.c ./srcs_bonus/interact_bonus.c


OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror

MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

bonus: $(OBJS_BONUS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

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