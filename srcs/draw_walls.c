/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:54:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/19 03:50:39 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double dabs(double d)
{
	if(d < 0)
		return (d * -1);
	else
		return (d);
}

void	draw_walls(t_cub *cub)
{
	int x;

	t_ray *r;
	r = malloc(sizeof(t_ray));

	x = 0;
	
	while (x < cub->winsize_x-1)
	{
		r->cameraX = 2 * x /(double)cub->winsize_x - 1;
		r->rayDirX = cub->player->dir->x + cub->player->plane->x * r->cameraX;
		r->rayDirY = cub->player->dir->y + cub->player->plane->y * r->cameraX;
		r->mapX = (int)cub->player->pos->x;
		r->mapY = (int)cub->player->pos->y;
		r->hit = 0;
		if(r->rayDirX == 0)
			r->deltaDistX = 1e30;
		else
			r->deltaDistX = dabs(1/r->rayDirX);
		if(r->rayDirY == 0)
			r->deltaDistY = 1e30;
		else
			r->deltaDistY = dabs(1/r->rayDirY);
		if(r->rayDirX < 0)
		{
			r->stepX = -1;
			r->sideDistX = (cub->player->pos->x - r->mapX) * r->deltaDistX;
		}
		else
		{
			r->stepX = 1;
			r->sideDistX = (r->mapX + 1.0 - cub->player->pos->x) * r->deltaDistX;
		}
		if(r->rayDirY < 0)
		{
			r->stepY = -1;
			r->sideDistY = (cub->player->pos->y - r->mapY) * r->deltaDistY;
		}
		else
		{
			r->stepY = 1;
			r->sideDistY = (r->mapY + 1.0 - cub->player->pos->y ) * r->deltaDistY;
		}
		while(!r->hit)
		{
			if(r->sideDistX < r->sideDistY)
			{
				r->sideDistX += r->deltaDistX;
				r->mapX += r->stepX;
				r->side = 0;
			}
			else
			{
				r->sideDistY += r->deltaDistY;
				r->mapY += r->stepY;
				r->side = 1;
			}
			if(has_hitVoid(cub,r->mapX,r->mapY))
				r->hit = 1;
			// printf("mapX=%d, mapY=%d, map_size_x=%d, map_size_y=%d\n", mapX, mapY, cub->map_size_x, cub->map_size_y);
			else if(has_hitWall(cub,r->mapX,r->mapY))
			{
				// put_pixel(cub->buffer,x,384,create_argb(0,255,0,0));
				if(r->side)
				{
					// h = mapY + (1 - stepY) / 2;
					r->perpWallDist = (r->sideDistY - r->deltaDistY);
				}
				else
				{
					// h = mapX + (1 - stepX) / 2;
					r->perpWallDist = (r->sideDistX - r->deltaDistX);
				}
				r->hit = 1;
				r->lineHeight = (int) (cub->winsize_y / r->perpWallDist);
				r->drawStart = -r->lineHeight / 2 + cub->winsize_y / 2;
				if(r->drawStart < 0)
					r->drawStart = 0;
				r->drawEnd = r->lineHeight / 2 + cub->winsize_y / 2;
				if(r->drawEnd >= cub->winsize_y)
					r->drawEnd = cub->winsize_y - 1;
				if(cub->map[r->mapX][r->mapY])
				// selectDrawWalls(ray,cub);
				drawVertical(cub,r,x);
				// printf("Hit x:%d MAPX:%dMAPY:%d\n",x,mapX,mapY);
			}
			// usleep(100);
		}
		x ++;
	}
	free(r);
}

void drawVertical(t_cub *cub, t_ray *r, int x)
{
	// float ratio;
	int color;

	while (r->drawStart < r->drawEnd)
	{
		// ratio = r->drawStart / (float)(cub->winsize_y);
		color = wall_shade(r->perpWallDist,r->side);
		// color = color_mult(color,ratio);
		// printf("oh %d %d\n",start,end);
		put_pixel(cub->buffer,x,r->drawStart,color);
		r->drawStart ++;
	}
}

int wall_shade(double dist, int side)
{
	float clamped_dist;

	clamped_dist = 1.0f - ((dist) / (SHADE_DIST)) ;
	if(dist < 0)
		clamped_dist = 1;
	if(dist > SHADE_DIST)
		clamped_dist = 0;
	if(side)
		clamped_dist *= .75;
	return(create_argb(0,255 * clamped_dist ,0,0));
}

int has_hitWall(t_cub *cub, int mapX, int mapY)
{
	if(cub->map[mapX][mapY] == WALL)
		return (1);
	else
		return (0);
}

int has_hitVoid(t_cub *cub, int mapX, int mapY)
{
	if(mapX < 0 || mapX >= cub->map_size_x)
		return (1);
	else if(mapY < 0 || mapY >= cub->map_size_y)
		return (1);
	else
		return (0);
}