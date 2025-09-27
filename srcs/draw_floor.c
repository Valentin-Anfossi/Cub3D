/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:22:20 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/27 22:15:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_floor_helper(t_cub *c, t_ray *r,int x, int y);


void draw_floor(t_cub *cub)
{
	t_ray *r;
	t_player *p;
	int y;
	int x;
	
	r = malloc(sizeof(t_ray));
	p = cub->player;
	r->rayDirX = p->dir->x - p->plane->x;
	r->rayDirY = p->dir->y - p->plane->y;
	r->rayDirX1 = p->dir->x + p->plane->x;
	r->rayDirY1 = p->dir->y + p->plane->y;
	y = 0;
	x = 0;
	while(y < cub->winsize_y - 1)
	{
		x = 0;
		r->rowDistance = (0.5 * cub->winsize_y) / (y - cub->winsize_y / 2);
		r->floorStepX = r->rowDistance *(r->rayDirX1 - r->rayDirX) / cub->winsize_x;
		r->floorStepY = r->rowDistance *(r->rayDirY1 - r->rayDirY) / cub->winsize_x;
		r->floorX = p->pos->x + r->rowDistance * r->rayDirX;
		r->floorY = p->pos->y + r->rowDistance * r->rayDirY;
		while(x < cub->winsize_x - 1)
		{
			draw_floor_helper(cub,r,x,y);
			x ++;	
		}
		y ++;
	}
}

void draw_floor_helper(t_cub *c, t_ray *r,int x, int y)
{
	int cellX;
	int cellY;
	int tx;
	int ty;
	int color;
	float shade;

	shade = wall_shade(r->rowDistance,0);
	cellX = (int)(r->floorX);
	cellY = (int)(r->floorY);
	tx = (int)(c->texture_cl->width * (r->floorX - cellX)) & (c->texture_cl->width - 1);
	ty = (int)(c->texture_cl->height * (r->floorY - cellY)) & (c->texture_cl->height - 1);
	r->floorX += r->floorStepX;
	r->floorY += r->floorStepY;
	if(y > c->winsize_y/2)
	{
		color = get_TexPixel(tx,ty,c->texture_fl);
		color = color_mult_fast(color,shade,c);
		put_pixel(c->buffer,x,y,color);
	}
	color = get_TexPixel(tx,ty,c->texture_cl);
	color = color_mult_fast(color,shade,c);
	put_pixel(c->buffer,x,c->winsize_y - y - 1,color);
}