/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/12/08 22:33:47 by vanfossi         ###   ########.fr       */
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
#define SPRITE 3
#define DOOR_V 4
#define DOOR_H 5
#define P_NORTH 6
#define P_SOUTH 7
#define P_EAST 8
#define P_WEST 9
#define MAP_SIZE 500
#define FOV 90
#define SHADE_DIST 7

#define WIN_SIZEX 900
#define WIN_SIZEY 600

#define ERROR_MAP 2
#define ERROR_INPUT 1

#define MULT 128

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_STLEFT 97
#define KEY_STRIGHT 100
#define KEY_MOUSE 112
#define TARGET_FPS 60
#define ROT_SPEED 0.05

typedef struct s_v3
{
	int		x;
	int		y;
	int		z;
}	t_v3;

typedef struct s_intv2
{
	int	x;
	int	y;
}	t_intv2;

typedef struct s_v2
{
	float	x;
	float	y;
}	t_v2;

typedef struct s_draw
{
	void			*img;
	unsigned char	*data;
	int				bpp;
	int				length;
	int				endian;
	int				pos_x;
	int				pos_y;
	int				width;
	int				height;
}			t_draw;

typedef struct s_bk
{
	int		x;
	int		y;
	float	rt;
}			t_bk;

typedef struct s_vert
{
	float	wall_x;
	float	tex_pos;
	int		tex_x;
	int		tex_y;
	float	step;
	int		shade;
	t_draw	*cur_tex;
}	t_vert;

typedef struct s_player
{
	int		col_true;
	t_v2	*pos;
	t_v2	*dir;
	t_v2	*plane;
	t_v3	*input;
	float	speed;
	float	rot_speed;
}	t_player;

typedef struct s_cub
{
	void			*mlx;
	void			*window;
	t_player		*player;

	t_draw			*buffer;
	t_draw			*buffer_old;
	t_draw			*background;
	t_draw			*texture_no;
	t_draw			*texture_so;
	t_draw			*texture_we;
	t_draw			*texture_ea;
	char			*no_texpath;
	char			*so_texpath;
	char			*we_texpath;
	char			*ea_texpath;
	unsigned int	shade_lut[256][256];
	int				winsize_x;
	int				winsize_y;
	int				errnum;
	int				debug;
	int				map_fd;
	int				map_size_x;
	int				map_size_y;
	int				ce_color;
	int				fl_color;
	char			**map_str;
	int				**map;
	float			**floatmap;
	float			*zbuffer;
	int				*player_pos;
	struct timeval	start_time;
	struct timeval	time;
	struct timeval	old_time;
	double			delta_time;
}	t_cub;

typedef struct s_ray
{
	float	camera_x;
	float	raydir_x;
	float	raydir_x1;
	float	raydir_y;
	float	raydir_y1;
	float	side_disty;
	float	side_distx;
	float	delta_distx;
	float	delta_disty;
	float	perpwall_dist;
	float	floor_stepx;
	float	floor_stepy;
	float	row_distance;
	float	floor_x;
	float	floor_y;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
}	t_ray;

//FUNCTIONS

//INIT.C
t_cub	*init(int argc, char **argv);
t_cub	*create_cub(char *path);
void	init_map(t_cub *cub);
int		get_playerinitialdir(t_cub *c);
void	init_shadelut(t_cub *cub);
void	init_floatmap(t_cub *c);
void	set_floatmap(t_cub *c);
void	init_zbuffer(t_cub *c);

//CLEAN.C
void	free_texture(t_cub *cub);
void	free_player(t_player *p);
void	free_map(t_cub *cub);
void	free_all(t_cub *cub);
int		destroystuff(t_cub *cub);

//MAP.C
void	map_init(t_cub *cub);
void	map_parse(char *line, t_cub *cub);
void	map_parse2(t_cub *cub);
void	add_to_map(int x, int y, t_cub *cub);
int		map_sizex(t_cub *cub);

//COLORS_UTILS.C
int		color_mult(int color, float ratio);
float	remap(float ratio, float low, float high);
int		create_argb(int alpha, int r, int g, int b);
int		color_mult_fast(int color, int ratio, t_cub *cub);

//PARSEUTILS.C
char	*parse_texturepath(char *line);
int		parse_color(char *line);

//ERRORS.C
void	error_exit(t_cub *c);

//DEBUG
void	debug_printcub(t_cub *cub);
void	draw_debug(t_cub *cub);

t_draw	*draw_background(t_cub *cub);

//CLEAN.C
void	free_all(t_cub *cub);
void	free_texture(t_cub *cub);
int		destroystuff(t_cub *cub);

//DRAW_WALLS.C
void	draw_walls(t_cub *cub);
void	init_walls(t_cub *cub);
int		has_hitwall(t_cub *cub, int map_x, int map_y);
void	draw_vertical(t_cub *cub, t_ray *r, int x);
int		has_hitvoid(t_cub *cub, int map_x, int map_y);
float	wall_shade(float dist, int side);
int		get_texpixel(int x, int y, t_draw *img);

//DRAWER.C
void	put_pixel(t_draw *img, int x, int y, int color);

//FT_MEMCPYFAST.C
void	*ft_memcpyfast(void *dest, const void *src, size_t n);

//MAIN.C
t_v2	rotate_vector(const t_v2 *vector, int deg);

//DRAW_FLOOR.C
void	draw_floor(t_cub *cub);
void	draw_ceiling(t_cub *cub);

//DRAW_DOORS.C
void	drawDoor(t_cub *c, t_ray *r, int x);
int		drawDoor_H(t_cub *c, t_ray *r, int x);
void	drawDoor_V(t_cub *c, t_ray *r, int x);
int		has_hitDoor(t_cub *cub, int map_x, int map_y);
void	drawDoor_H2(t_cub *c, t_ray *r, int x);

//DRAW_UTILS.C
double	dabs(double d);
int		get_texpixel(int x, int y, t_draw *img);
float	wall_shade(float dist, int side);
int		has_hitwall(t_cub *cub, int map_x, int map_y);
int		has_hitvoid(t_cub *cub, int map_x, int map_y);
void	ray_helper(t_cub *cub, t_ray *r, int x);
int		init_img(t_cub *cub);
int		handle_key(int keycode, t_cub *cub);
int		handle_keyrelease(int keycode, t_cub *cub);
void	move_player(t_cub *c);
void	set_playerinitialrot(t_cub *c);

//CHECK_MAP.C

void	check_map(t_cub *c);
void	exit_maperror(t_cub *c);
t_draw	*init_background(t_cub *cub);
t_draw	*draw_background(t_cub *cub);
float	normimerde(t_cub *c, int bky);
t_bk	init_bkstruct(void);
int		map_sizex(t_cub *cub);

//CHECK_PLAYER.C
int player_check(t_cub *c);

//CHECK_INIT.C
int check_init(t_cub *c);
