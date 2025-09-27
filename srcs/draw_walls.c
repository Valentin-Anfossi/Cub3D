/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:54:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/24 08:12:23 by vanfossi         ###   ########.fr       */
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
	
	while (x < cub->winsize_x-1) //pour chaque colonne de lecran
	{
		r->cameraX = 2 * x /(double)cub->winsize_x - 1;
		r->rayDirX = cub->player->dir->x + cub->player->plane->x * r->cameraX;
		r->rayDirY = cub->player->dir->y + cub->player->plane->y * r->cameraX;
		r->mapX = (int)cub->player->pos->x;
		r->mapY = (int)cub->player->pos->y;
		r->hit = 0;
		if(r->rayDirX == 0)
			r->deltaDistX = 1e30; // C pour remplacer INFINITY car je crois que c'est pas autorise (a verif)
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
			else if(has_hitWall(cub,r->mapX,r->mapY))
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
				if(cub->map[r->mapX][r->mapY])
				drawVertical(cub,r,x);
			}
		}
		x ++;
	}
	free(r);
}

void drawVertical(t_cub *cub, t_ray *r, int x)
{
	float wallX;
	float texPos;
	int texX;
	int texY;
	float step;
	int shade;
	t_draw *curTex;
	

		if(r->side == 0)
	{
		if(r->stepX == -1) //NORD
			curTex = cub->texture_no;
		else // SUD
			curTex = cub->texture_so;
	}
	else
	{
		if(r->stepY == -1) // OUEST
			curTex = cub->texture_we;
		else // EST
			curTex = cub->texture_ea;
	}
	
	if(r->side == 0)
		wallX = cub->player->pos->y + r->perpWallDist * r->rayDirY;
	else
		wallX = cub->player->pos->x + r->perpWallDist * r->rayDirX;
	wallX -= floor(wallX);
	
	texX = (int)(wallX * (float)curTex->width);

	
	if(r->side == 0 && r->rayDirX > 0)
		texX = curTex->width - texX - 1;
	if(r->side == 1 && r->rayDirY < 0)
		texX = curTex->width - texX - 1;

	step = 1.0 * curTex->height/r->lineHeight; //ratio pixel texture/pixel line
	texPos = (r->drawStart - (cub->winsize_y/2) + r->lineHeight / 2) * step; 
	shade = wall_shade(r->perpWallDist,r->side);
	// (void)shade;
	while (r->drawStart < r->drawEnd)
	{
		texY = (int)texPos & (curTex->height-1); // en gros c'est comme faire un modulo % mais en bitshifting
		texPos += step;
		put_pixel(cub->buffer,x,r->drawStart,color_mult_fast(get_TexPixel(texX,texY,curTex),shade,cub));
		// put_pixel(cub->buffer,x,r->drawStart,get_TexPixel(texX,texY,curTex));
		r->drawStart ++;
	}
}

int get_TexPixel(int x, int y, t_draw *img)
{
	unsigned char *pixel;
	int color;

	if(x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0x000000);
	pixel = img->data + (y * img->length + x * (img->bpp / 8)); // on peut aussi precalc bpp/8 dans la struct de l'image ?
	if(img->endian == 1)
		color = (pixel[0] << 16) | (pixel[1] << 8) | pixel[2] << 0;	
	else
		color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0] << 0;
	return (color);
}

float wall_shade(float dist, int side)
{
	float clamped_dist;
	
	if(dist <= 0)
		return (255);
	if(dist >= SHADE_DIST)
		return (0);
	clamped_dist = 1.0f - (dist /SHADE_DIST);
	if(side)
		clamped_dist *= .75;
	return (int)(clamped_dist * 255.0f);
	
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
