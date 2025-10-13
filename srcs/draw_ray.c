/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:56:12 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 10:28:02 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_start(t_cub *cub, t_ray *r, int x)
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
}

void	ray_dir(t_cub *cub, t_ray *r)
{
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
}

void ray_side(t_ray *r)
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
}

void ray_hit(t_cub *cub, t_ray *r)
{
	if(r->side)
	{
		r->perpWallDist = (r->sideDistY - r->deltaDistY);
	}
	else
	{
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
}

void	ray_helper(t_cub *cub, t_ray *r, int x)
{
	ray_start(cub,r,x);
	ray_dir(cub,r);
	while(!r->hit)
	{
		ray_side(r);
		if(has_hitVoid(cub,r->mapX,r->mapY))
			r->hit = 1;
		else if(has_hitWall(cub,r->mapX,r->mapY))
		{
			ray_hit(cub,r);
			if(cub->map[r->mapX][r->mapY])
				drawVertical(cub,r,x);
		}
	}
}
