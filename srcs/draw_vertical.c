/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:22:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/11 18:12:04 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawVside(t_cub *cub, t_ray *r, t_vert *v)
{
	if(r->side == 0)
	{
		if(r->stepX == -1)
			v->curTex = cub->texture_no;
		else
			v->curTex = cub->texture_so;
	}
	else
	{
		if(r->stepY == -1)
			v->curTex = cub->texture_we;
		else
			v->curTex = cub->texture_ea;
	}
	if(r->side == 0)
		v->wallX = cub->player->pos->y + r->perpWallDist * r->rayDirY;
	else
		v->wallX = cub->player->pos->x + r->perpWallDist * r->rayDirX;
	v->wallX -= floor(v->wallX);
}

void drawVertical(t_cub *cub, t_ray *r, int x)
{
	t_vert *v;

	v = malloc(sizeof(t_vert));
	drawVside(cub,r,v);
	v->texX = (int)(v->wallX * (float)v->curTex->width);
	if(r->side == 0 && r->rayDirX > 0)
		v->texX = v->curTex->width - v->texX - 1;
	if(r->side == 1 && r->rayDirY < 0)
		v->texX = v->curTex->width - v->texX - 1;
	v->step = 1.0 * v->curTex->height/r->lineHeight;
	v->texPos = (r->drawStart - (cub->winsize_y/2) + r->lineHeight / 2) * v->step; 
	v->shade = wall_shade(r->perpWallDist,r->side);
	while (r->drawStart < r->drawEnd)
	{
		v->texY = (int)v->texPos & (v->curTex->height-1);
		v->texPos += v->step;
		put_pixel(cub->buffer,x,r->drawStart,
			color_mult_fast(get_TexPixel(v->texX,v->texY,v->curTex),v->shade,cub));
		r->drawStart ++;
	}
	free(v);
}
