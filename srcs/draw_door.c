/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:19:25 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/04 12:46:34 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int drawDoor_H(t_cub *c, t_ray *r, int x)
{
    if (c->map[r->mapX][r->mapY] != DOOR_H)
        return (0);

    float doorX = r->mapX + 0.5;
    float t = (doorX - c->player->pos->x) / r->rayDirX;
    float yIntersect = c->player->pos->y + t * r->rayDirY;
    
	if (yIntersect >= r->mapY && yIntersect <= r->mapY + 1)
    {
        r->perpWallDist = fabs(t);
		c->zbuffer[x] = r->perpWallDist;
         r->lineHeight = (int)(c->winsize_y / r->perpWallDist);
        r->drawStart = -r->lineHeight / 2 + c->winsize_y / 2;
        if (r->drawStart < 0) r->drawStart = 0;
        r->drawEnd = r->lineHeight / 2 + c->winsize_y / 2;
        if (r->drawEnd >= c->winsize_y) r->drawEnd = c->winsize_y - 1;
        drawDoor_H2(c, r, x);
        r->hit = 1;
        return (1);
    }
    return (0);
}

void drawDoor_H2(t_cub *c, t_ray *r, int x)
{
	float wallX;
	float texPos;
	int texX;
	int texY;
	float step;
	t_draw *curTex;
	
	curTex = c->texture_do;
	
	if(r->side == 0)
		wallX = c->player->pos->y + r->perpWallDist * r->rayDirY;
	else
		wallX = c->player->pos->x + r->perpWallDist * r->rayDirX;
	wallX -= floor(wallX);
	
	texX = (int)(wallX * (float)curTex->width);

	
	// if(r->side == 0 && r->rayDirX > 0)
	// 	texX = curTex->width - texX - 1;
	// if(r->side == 1 && r->rayDirY < 0)
	// 	texX = curTex->width - texX - 1;

	step = 1.0 * curTex->height/r->lineHeight; //ratio pixel texture/pixel line
	texPos = (r->drawStart - (c->winsize_y/2) + r->lineHeight / 2) * step; 
	// (void)shade;
	while (r->drawStart < r->drawEnd)
	{
		texY = (int)texPos & (curTex->height-1); // en gros c'est comme faire un modulo % mais en bitshifting
		texPos += step;
		// put_pixel(c->buffer,x,r->drawStart,0xFFFFFF);
		put_pixel(c->buffer,x,r->drawStart,get_TexPixel(texX,texY,curTex));
		r->drawStart ++;
	}	
}
