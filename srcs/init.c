/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/04 03:37:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_cub	*init(int argc, char **argv)
{
	t_cub	*cub;
	int		test_fd;

	(void)argc;
	(void)argv;
	if (argc != 2)
		return (0);
	if (!argv[1])
		return (0);
	test_fd = open(argv[1], O_RDONLY);
	if (test_fd < 0)
		return (NULL);
	close(test_fd);
	cub = create_cub(argv[1]);
	return (cub);
}

int	data_img(t_cub *cub)
{
	cub->texture_no->data = (unsigned char*)mlx_get_data_addr(cub->texture_no->img,
			&cub->texture_no->bpp, &cub->texture_no->length,
			&cub->texture_no->endian);
	cub->texture_so->data = (unsigned char*)mlx_get_data_addr(cub->texture_so->img,
			&cub->texture_so->bpp, &cub->texture_so->length,
			&cub->texture_so->endian);
	cub->texture_ea->data = (unsigned char*)mlx_get_data_addr(cub->texture_ea->img,
			&cub->texture_ea->bpp, &cub->texture_ea->length,
			&cub->texture_ea->endian);
	cub->texture_we->data = (unsigned char*)mlx_get_data_addr(cub->texture_we->img,
			&cub->texture_we->bpp, &cub->texture_we->length,
			&cub->texture_we->endian);
	if (!cub->texture_no->data || !cub->texture_so->data
		|| !cub->texture_ea->data || !cub->texture_we->data)
		return (1);
	return (0);
}

int	data_img_bonus(t_cub *cub)
{
	cub->texture_cl->data = (unsigned char*)mlx_get_data_addr(cub->texture_cl->img,
			&cub->texture_cl->bpp, &cub->texture_cl->length,
			&cub->texture_cl->endian);
	cub->texture_fl->data = (unsigned char*)mlx_get_data_addr(cub->texture_fl->img,
			&cub->texture_fl->bpp, &cub->texture_fl->length,
			&cub->texture_fl->endian);
	cub->texture_do->data = (unsigned char*)mlx_get_data_addr(cub->texture_do->img,
			&cub->texture_do->bpp, &cub->texture_do->length,
			&cub->texture_do->endian);
	if (!cub->texture_fl->data || !cub->texture_cl->data)
		return (1);
	return (0);
}

t_draw *init_buffer(t_cub *cub)
{
	t_draw	*buffer;

	buffer = malloc(sizeof(t_draw));
	buffer->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!buffer->img)
		return (NULL);
	buffer->data = (unsigned char*)mlx_get_data_addr
		(buffer->img, &buffer->bpp,
			&buffer->length, &buffer->endian);
	if (!buffer->data)
	{
		mlx_destroy_image(cub->mlx, buffer->img);
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	init_img(t_cub *cub)
{
	cub->buffer = init_buffer(cub);
	cub->buffer_old = init_buffer(cub);
	cub->background = draw_background(cub);
	if (!cub->buffer)
		return (1);
	cub->texture_no = malloc(sizeof(t_draw));
	cub->texture_so = malloc(sizeof(t_draw));
	cub->texture_we = malloc(sizeof(t_draw));
	cub->texture_ea = malloc(sizeof(t_draw));
	cub->texture_no->img = mlx_xpm_file_to_image(cub->mlx, cub->no_texpath,
			&cub->texture_no->width, &cub->texture_no->height);
	cub->texture_so->img = mlx_xpm_file_to_image(cub->mlx, cub->so_texpath,
			&cub->texture_so->width, &cub->texture_so->height);
	cub->texture_we->img = mlx_xpm_file_to_image(cub->mlx, cub->we_texpath,
			&cub->texture_we->width, &cub->texture_we->height);
	cub->texture_ea->img = mlx_xpm_file_to_image(cub->mlx, cub->ea_texpath,
			&cub->texture_ea->width, &cub->texture_ea->height);
	if (!cub->texture_no->img || !cub->texture_so->img
		|| !cub->texture_we->img || !cub->texture_ea->img)
		return (1);
	if (data_img(cub))
		return (1);
	return (0);
}

int init_img_bonus(t_cub *cub)
{
	cub->texture_cl = malloc(sizeof(t_draw));
	cub->texture_fl = malloc(sizeof(t_draw));
	cub->texture_do = malloc(sizeof(t_draw));
	cub->texture_cl->img = mlx_xpm_file_to_image(cub->mlx, cub->cl_texpath,
			&cub->texture_cl->width, &cub->texture_cl->height);
	cub->texture_fl->img = mlx_xpm_file_to_image(cub->mlx, cub->fl_texpath,
			&cub->texture_fl->width, &cub->texture_fl->height);
	cub->texture_do->img = mlx_xpm_file_to_image(cub->mlx, cub->do_texpath,
			&cub->texture_do->width, &cub->texture_do->height);
	if (!cub->texture_cl->img || !cub->texture_fl->img || !cub->texture_do->img)
		return (1);
	if (data_img_bonus(cub))
		return (1);
	return (0);	
}

int get_playerInitialDir(t_cub *c)
{
	int i;

	i = c->map[c->player_pos[0]][c->player_pos[1]];
	if (i == P_NORTH)
		return (90);
	else if (i == P_SOUTH)
		return (260);
	else if (i == P_EAST)
		return (0);
	else
		return (180);
}

t_player *player_init(t_cub *cub)
{
	t_player *p;

	p = malloc(sizeof(t_player));
	p->pos = malloc(sizeof(t_v2));
	p->plane = malloc(sizeof(t_v2));
	p->input = malloc(sizeof(t_v3));
	p->dir = malloc(sizeof(t_v2));
	printf("playerpos:%d,%d\n",cub->player_pos[0],cub->player_pos[1]);
	// p->dir =  get_playerInitialDir(cub->map[cub->player_pos[0]][cub->player_pos[1]]);
	p->dir->x = 0.0;
	p->dir->y = 1.0;
	p->pos->x = (float)cub->player_pos[0]+.5;
	p->pos->y = (float)cub->player_pos[1]+.5;
	p->plane->x = 0.66;
	p->plane->y = 0.0;
	p->speed = .05;
	p->rot_speed = ROT_SPEED;
	p->input->x = 0;
	p->input->y = 0;
	p->input->z = 0;
	p->col_true = COL_TRUE;
	return (p);
	
}

t_cub	*create_cub(char *path)
{
	t_cub	*cub;

	(void)path;
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->mlx = mlx_init();
	cub->winsize_x = WIN_SIZEX;
	cub->winsize_y = WIN_SIZEY;
	cub->map_fd = open(path, O_RDONLY);
	cub->map_str = NULL;
	cub->errnum = 0;
	cub->debug = 0;
	cub->no_texpath = NULL;
	cub->so_texpath = NULL;
	cub->we_texpath = NULL;
	cub->ea_texpath = NULL;
	cub->ce_color = 0;
	cub->fl_color = 0;
	cub->player_pos = malloc(sizeof(int)*2);
	cub->is_mouseActive = 0;
	cub->delta_time = 0;
	map_init(cub);
	if (init_img(cub))
		return (NULL);
	if(BONUS == 1)
		if(init_img_bonus(cub))
			return (NULL);
	cub->window = mlx_new_window
		(cub->mlx, cub->winsize_x, cub->winsize_y, "Cub3d");
	if (!cub->window)
	{
		free(cub);
		return (NULL);
	}
	cub->player = player_init(cub);
	init_shadelut(cub);
	gettimeofday(&(cub->start_time), NULL);
	init_floatmap(cub);
	init_zbuffer(cub);
	debug_printcub(cub);
	return (cub);
}

void init_zbuffer(t_cub *c)
{
	int i;
	
	i = 0;
	c->zbuffer = malloc(sizeof(float) * c->winsize_x);
	while(i < c->winsize_x)
	{
		c->zbuffer[i] = 0.0f;
		i ++;	
	}
}

void set_floatmap(t_cub *c)
{
	int x;
	int y;

	x = 0;
	while(x < c->map_size_x)
	{
		y = 0;
		while(y < c->map_size_y)
		{
			if(c->map[x][y] == WALL || c->map[x][y] == DOOR_V || c->map[x][y] == DOOR_H)
				c->floatmap[x][y] = 1.0f;
			else
				c->floatmap[x][y] = 0.0f;
			y ++;
		}
		x ++;
	}
}

void init_floatmap(t_cub *c)
{
	int i;

	i = 0;
	c->floatmap = (float **)malloc(sizeof(float *) * c->map_size_x);
	while(i < c->map_size_x)
	{
		c->floatmap[i] = malloc(sizeof(float) * c->map_size_y);
		if(!c->floatmap[i])
			return;
		i ++;
	}
	set_floatmap(c);
}

void init_shadelut(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(x < 256)
	{
		while (y < 256)
		{
			cub->shade_lut[x][y] = (int)((x * y) / 255.0f);
			y ++;
		}
		y = 0;
		printf("\n");
		x ++;
	}
}

void	init_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->map_size_x)
	{
		y = 0;
		while (y < cub->map_size_y)
		{
			cub->map[x][y] = 0;
			y ++;
		}
		x ++;
	}
}
