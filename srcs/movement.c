/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:50:58 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 10:32:09 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_nocol(t_cub *c, t_player *p)
{
	float posX;
	float posY;

	posX = p->pos->x;
	posX += p->dir->x * p->input->x * p->speed;
	posX += -p->dir->y * p->input->z * p->speed;
	if(posX < c->map_size_x && posX > 0)
		p->pos->x = posX;
	
	posY = p->pos->y;
	posY += p->dir->y * p->input->x * p->speed;
	posY += p->dir->x * p->input->z * p->speed;
	if(posY < c->map_size_y && posY > 0)
		p->pos->y = posY;
}

void move_player(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	t_player *p;

	p = c->player;

	if(p->input->x != 0 || p->input->z != 0)
	{
			move_nocol(c,p);
	}
	if(p->input->y != 0)
	{
		oldDirX = p->dir->x;
		p->dir->x = p->dir->x * cos(p->rot_speed * p->input->y) - p->dir->y * sin(p->rot_speed * p->input->y);
		p->dir->y = oldDirX * sin(p->rot_speed * p->input->y) + p->dir->y * cos(p->rot_speed * p->input->y);
		oldPlaneX = p->plane->x;
		p->plane->x = p->plane->x * cos(p->rot_speed * p->input->y) - p->plane->y * sin(p->rot_speed * p->input->y);
		p->plane->y = oldPlaneX * sin(p->rot_speed * p->input->y) + p->plane->y * cos(p->rot_speed * p->input->y);
	}
}

t_v2 rotateVector(const t_v2 *vector, int deg)
{
	float f;
	t_v2 rotated;
	f = deg * M_PI / 180.0f;
	rotated.x = vector->x * cosf(f);
	rotated.y = vector->y * sinf(f);
	return (rotated);
}

void set_playerInitialRotation(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	t_player *p;
	int	angle_degrees;
	float angle;

	p = c->player;
	angle_degrees = get_playerInitialDir(c);
	angle = angle_degrees *  M_PI / 180.0;
	oldDirX = p->dir->x;
	p->dir->x = p->dir->x * cos(angle) - p->dir->y * sin(angle);
	p->dir->y = oldDirX * sin(angle) + p->dir->y * cos(angle);
	oldPlaneX = p->plane->x;
	p->plane->x = p->plane->x * cos(angle) - p->plane->y * sin(angle);
	p->plane->y = oldPlaneX * sin(angle) + p->plane->y * cos(angle);
}
