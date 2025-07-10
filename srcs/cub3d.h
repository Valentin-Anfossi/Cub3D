/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/10 17:50:26 by vanfossi         ###   ########.fr       */
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

//INIT/MAP
t_cub	*init(int argc, char **argv);
t_cub	*create_cub(char *path);
void	map_init(t_cub *cub);

//PARSING
char *parse_texturepath(char *line);
int	parse_color(char *line);

//DEBUG
void	debug_printcub(t_cub *cub);
