# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 17:41:00 by vanfossi          #+#    #+#              #
#    Updated: 2026/01/30 19:58:59 by vanfossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

LIBFT	= ./libft/libft.a

SRCSFILES	= 	check_map.c check_map2.c clean.c \
			colors_utils.c debug.c draw_background.c \
			draw_ray.c draw_utils.c draw_vertical.c \
			draw_walls.c drawer.c errors.c \
			ft_memcpyfast.c handle_keys.c img.c \
			init.c init2.c init3.c main.c \
			map_utils.c map.c movement.c \
			parseutils.c file_check.c map_check.c \
			map_check2.c check_mapstr.c check_player.c \
			map_init.c gnl_cleaner.c
SRCS = 		$(addprefix ./srcs/,$(SRCSFILES))
OBJS = 		$(patsubst ./srcs/%.c,obj/%.o,$(SRCS))

SRCS_BONUSFILES  = 	bonus2_bonus.c bonus3_bonus.c bonus_bonus.c \
				check_map2_bonus.c check_map_bonus.c check_mapstr_bonus.c \
				check_player_bonus.c clean_bonus.c colors_utils_bonus.c \
				debug_bonus.c draw_background_bonus.c drawer_bonus.c \
				draw_ray_bonus.c draw_utils_bonus.c draw_vertical_bonus.c \
				draw_walls_bonus.c errors_bonus.c file_check_bonus.c \
				ft_memcpyfast_bonus.c handle_keys_bonus.c img_bonus.c \
				init2_bonus.c init3_bonus.c init_bonus.c main_bonus.c\
				map_bonus.c map_check2_bonus.c map_check_bonus.c \
				map_init_bonus.c map_utils_bonus.c movement_bonus.c parseutils_bonus.c \
				gnl_cleaner_bonus.c interact_bonus.c draw_utils2_bonus.c
SRCS_BONUS = $(addprefix ./srcs_bonus/,$(SRCS_BONUSFILES))
OBJS_BONUS = $(patsubst ./srcs_bonus/%.c,obj_bonus/%.o,$(SRCS_BONUS))

CC = cc

FLAGS = -Wall -Wextra -Werror

MLX = ./minilibx-linux/libmlx_Linux.a

all: $(NAME)

bonus: $(OBJS_BONUS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME) -lX11 -lXext -lm -O3

obj_bonus/%.o: ./srcs_bonus/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

obj/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

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