/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:50:58 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 11:31:57 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_nocol(t_cub *c, t_player *p)
{
	float	pos_x;
	float	pos_y;

	pos_x = p->pos->x;
	pos_x += p->dir->x * p->input->x * p->speed;
	pos_x += -p->dir->y * p->input->z * p->speed;
	if (pos_x < c->map_size_y && pos_x > 0)
		p->pos->x = pos_x;
	pos_y = p->pos->y;
	pos_y += p->dir->y * p->input->x * p->speed;
	pos_y += p->dir->x * p->input->z * p->speed;
	if (pos_y < c->map_size_x && pos_y > 0)
		p->pos->y = pos_y;
}

void	move_player(t_cub *c)
{
	float		olddir_x;
	float		oldplane_x;
	t_player	*p;

	p = c->player;
	if (p->input->x != 0 || p->input->z != 0)
	{
		move_nocol(c, p);
	}
	if (p->input->y != 0)
	{
		olddir_x = p->dir->x;
		p->dir->x = p->dir->x * cos(p->rot_speed * p->input->y)
			- p->dir->y * sin(p->rot_speed * p->input->y);
		p->dir->y = olddir_x * sin(p->rot_speed * p->input->y)
			+ p->dir->y * cos(p->rot_speed * p->input->y);
		oldplane_x = p->plane->x;
		p->plane->x = p->plane->x * cos(p->rot_speed * p->input->y)
			- p->plane->y * sin(p->rot_speed * p->input->y);
		p->plane->y = oldplane_x * sin(p->rot_speed * p->input->y)
			+ p->plane->y * cos(p->rot_speed * p->input->y);
	}
}

t_v2	rotate_vector(const t_v2 *vector, int deg)
{
	float	f;
	t_v2	rotated;

	f = deg * M_PI / 180.0f;
	rotated.x = vector->x * cosf(f);
	rotated.y = vector->y * sinf(f);
	return (rotated);
}

void	set_playerinitialrot(t_cub *c)
{
	float		olddir_x;
	float		oldplane_x;
	t_player	*p;
	int			angle_degrees;
	float		angle;

	p = c->player;
	angle_degrees = get_playerinitialdir(c);
	angle = angle_degrees * M_PI / 180.0;
	olddir_x = p->dir->x;
	p->dir->x = p->dir->x * cos(angle) - p->dir->y * sin(angle);
	p->dir->y = olddir_x * sin(angle) + p->dir->y * cos(angle);
	oldplane_x = p->plane->x;
	p->plane->x = p->plane->x * cos(angle) - p->plane->y * sin(angle);
	p->plane->y = oldplane_x * sin(angle) + p->plane->y * cos(angle);
}
