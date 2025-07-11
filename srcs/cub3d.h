/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/11 05:00:02 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"

#define EMPTY 0
#define WALL 1
#define P_NORTH 6
#define P_SOUTH 7
#define P_EAST 8
#define P_WEST 9
#define MAP_SIZE 500


typedef struct {
	int x;
	int y;
	int z;
} t_v3;


typedef struct s_cub
{
	char *no_texpath;
	char *so_texpath;
	char *we_texpath;
	char *ea_texpath;
	
	int winsize_x;
	int winsize_y;
	
	int errnum;
	int debug;
	int map_fd;
	int map_size_x;
	int map_size_y;
	int ce_color;
	int fl_color;
	char **map_str;
	int **map;
}	t_cub;

//FUNCTIONS

//INIT.C
t_cub	*init(int argc, char **argv);
t_cub	*create_cub(char *path);
void 	init_map(t_cub *cub);

//MAP.C
void	map_init(t_cub *cub);
void map_parse(char *line, t_cub *cub);
void map_parse2(t_cub *cub);
void add_to_map(int x, int y, t_cub* cub);
int map_sizex(t_cub *cub);

//PARSEUTILS.C
char *parse_texturepath(char *line);
int	parse_color(char *line);

//ERRORS.C
void error_exit(t_cub *c);

//DEBUG
void	debug_printcub(t_cub *cub);
