/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:54:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/18 11:52:21 by vanfossi         ###   ########.fr       */
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
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int h;
	int lineHeight;
	int stepX;
	int stepY;
	int hit;
	int side;
	int mapX;
	int mapY;

	x = 0;
	
	while (x < cub->winsize_x-1)
	{
		cameraX = 2 * x /(double)cub->winsize_x - 1;
		rayDirX = cub->player->dir->x + cub->player->plane->x * cameraX;
		rayDirY = cub->player->dir->y + cub->player->plane->y * cameraX;
		mapX = (int)cub->player->pos->x;
		mapY = (int)cub->player->pos->y;
		hit = 0;
		if(rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = dabs(1/rayDirX);
		if(rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = dabs(1/rayDirY);
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player->pos->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player->pos->x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player->pos->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player->pos->y ) * deltaDistY;
		}
		while(!hit)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// printf("mapX=%d, mapY=%d, map_size_x=%d, map_size_y=%d\n", mapX, mapY, cub->map_size_x, cub->map_size_y);
			if(has_hitWall(cub,mapX,mapY,x))
			{
				// put_pixel(cub->buffer,x,384,create_argb(0,255,0,0));
				if(side)
				{
					h = mapY + (1 - stepY) / 2;
					perpWallDist = (sideDistY - deltaDistY);
				}
				else
				{
					h = mapX + (1 - stepX) / 2;
					perpWallDist = (sideDistX - deltaDistX);
				}
				hit = 1;
				lineHeight = (int) (h / perpWallDist);
				// printf("Hit x:%d MAPX:%dMAPY:%d\n",x,mapX,mapY);
				usleep(100);
			}
		}
		x ++;
	}
}

// Returns 0 if out of bounds, 1 if wall hit
int has_hitWall(t_cub *cub, int mapX, int mapY, int x)
{
	if(mapX < 0 || mapX >= cub->map_size_x)
	{
		put_pixel(cub->buffer,x,384,create_argb(0,0,0,0));
		return (1);
	}	
	else if(mapY < 0 || mapY >= cub->map_size_y)
	{
		put_pixel(cub->buffer,x,384,create_argb(0,0,0,0));
		return (1);
	}
	else if(cub->map[mapX][mapY] > 0)
	{
		put_pixel(cub->buffer,x,384,create_argb(0,255,0,0));
		return (1);
	}
	else
	{
		return (0);
	}
}