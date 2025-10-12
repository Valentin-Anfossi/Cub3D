/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 09:09:20 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 09:09:53 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player *player_init(t_cub *cub)
{
	t_player *p;

	p = malloc(sizeof(t_player));
	p->pos = malloc(sizeof(t_v2));
	p->plane = malloc(sizeof(t_v2));
	p->input = malloc(sizeof(t_v3));
	p->dir = malloc(sizeof(t_v2));
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
	return (p);
}

t_cub	*create_cub_h(char *path)
{
	t_cub	*cub;

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
	cub->delta_time = 0;
	return (cub);
}

t_cub	*create_cub(char *path)
{
	t_cub	*cub;

	cub = create_cub_h(path);
	map_init(cub);
	if (init_img(cub))
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
	return (cub);
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