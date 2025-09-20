/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/20 10:04:37 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "../libft/libft.h"
#include <math.h>
#include <sys/time.h>
#include <unistd.h>

#define EMPTY 0
#define WALL 1
#define P_NORTH 6
#define P_SOUTH 7
#define P_EAST 8
#define P_WEST 9
#define MAP_SIZE 500
#define FOV 90
#define SHADE_DIST 14

#define WIN_SIZEX 920
#define WIN_SIZEY 720

#define ERROR_MAP 2
#define ERROR_INPUT 1

#define MULT 128

#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define TARGET_FPS 60

typedef struct s_v3
{
	int		x;
	int		y;
	int		z;
}	t_v3;

typedef struct s_intv2
{
	int x;
	int y;
} t_intv2;

typedef struct s_v2
{
	double x;
	double y;
} t_v2;

typedef struct s_draw
{
	void	*img;
	char	*data;
	int		bpp;
	int		length;
	int		endian;
	int		pos_x;
	int		pos_y;
	int		width;
	int		height;
}			t_draw;

typedef struct s_player
{
	t_v2	*pos;
	t_v2	*dir;
	t_v2	*plane;
	t_intv2	*input;
	float	speed;
	float	rot_speed;
} t_player;

typedef struct s_cub
{
	void	*mlx;
	void	*window;
	t_player	*player;

	t_draw	*buffer;
	t_draw	*buffer_old;
	t_draw	*background;
	t_draw	*texture_no;
	t_draw	*texture_so;
	t_draw	*texture_we;
	t_draw	*texture_ea;
	char	*no_texpath;
	char	*so_texpath;
	char	*we_texpath;
	char	*ea_texpath;

	int		winsize_x;
	int		winsize_y;

	int		errnum;
	int		debug;
	int		map_fd;
	int		map_size_x;
	int		map_size_y;
	int		ce_color;
	int		fl_color;
	char	**map_str;
	int		**map;
	int		*player_pos;

	struct timeval  start_time;
	struct timeval	time;
	struct timeval	old_time;
	double	delta_time;
}	t_cub;

typedef struct s_ray {
	float cameraX;
	float rayDirX;
	float rayDirY;
	float sideDistY;
	float sideDistX;
	float deltaDistX;
	float deltaDistY;
	float perpWallDist;
	int drawStart;
	int drawEnd;
	int lineHeight;
	int stepX;
	int stepY;
	int hit;
	int side;
	int mapX;
	int mapY;
}	t_ray;

//FUNCTIONS

//INIT.C
t_cub	*init(int argc, char **argv);
t_cub	*create_cub(char *path);
void	init_map(t_cub *cub);
int 	get_playerInitialDir(t_cub *c);


//MAP.C
void	map_init(t_cub *cub);
void	map_parse(char *line, t_cub *cub);
void	map_parse2(t_cub *cub);
void	add_to_map(int x, int y, t_cub *cub);
int		map_sizex(t_cub *cub);

//COLORS_UTILS.C
int	color_mult(int color, float ratio);
float remap(float ratio,float low, float high);
int create_argb(int alpha, int r, int g, int b);

//PARSEUTILS.C
char	*parse_texturepath(char *line);
int		parse_color(char *line);

//ERRORS.C
void	error_exit(t_cub *c);

//DEBUG
void	debug_printcub(t_cub *cub);

t_draw	*draw_background(t_cub *cub);

//CLEAN.C
void	free_all(t_cub *cub);
void	free_texture(t_cub *cub);
int		destroystuff(t_cub *cub);

//DRAW_WALLS.C
void	draw_walls(t_cub *cub);
void	init_walls(t_cub *cub);
int has_hitWall(t_cub *cub, int mapX, int mapY);
void drawVertical(t_cub *cub, t_ray *r, int x);
int has_hitVoid(t_cub *cub, int mapX, int mapY);
float wall_shade(float dist,int side);
int get_TexPixel(int x, int y, t_draw *img);

//DRAWER.C
void	put_pixel(t_draw *img, int x, int y, int color);

//FT_MEMCPYFAST.C
void	*ft_memcpyfast(void *dest, const void *src, size_t n);