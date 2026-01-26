/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:56:12 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/08 10:27:20 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ray_start(t_cub *cub, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)cub->winsize_x - 1;
	r->raydir_x = cub->player->dir->x + cub->player->plane->x * r->camera_x;
	r->raydir_y = cub->player->dir->y + cub->player->plane->y * r->camera_x;
	r->map_x = (int)cub->player->pos->x;
	r->map_y = (int)cub->player->pos->y;
	r->hit = 0;
	if (r->raydir_x == 0)
		r->delta_distx = 1e30;
	else
		r->delta_distx = dabs(1 / r->raydir_x);
	if (r->raydir_y == 0)
		r->delta_disty = 1e30;
	else
		r->delta_disty = dabs(1 / r->raydir_y);
}

void	ray_dir(t_cub *cub, t_ray *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_distx = (cub->player->pos->x - r->map_x) * r->delta_distx;
	}
	else
	{
		r->step_x = 1;
		r->side_distx = (r->map_x + 1.0 - cub->player->pos->x) * r->delta_distx;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_disty = (cub->player->pos->y - r->map_y) * r->delta_disty;
	}
	else
	{
		r->step_y = 1;
		r->side_disty = (r->map_y + 1.0 - cub->player->pos->y)
			* r->delta_disty;
	}
}

void	ray_side(t_ray *r)
{
	if (r->side_distx < r->side_disty)
	{
		r->side_distx += r->delta_distx;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_disty += r->delta_disty;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

void	ray_hit(t_cub *cub, t_ray *r)
{
	if (r->side)
	{
		r->perpwall_dist = (r->side_disty - r->delta_disty);
	}
	else
	{
		r->perpwall_dist = (r->side_distx - r->delta_distx);
	}
	r->hit = 1;
	r->line_height = (int)(cub->winsize_y / r->perpwall_dist);
	r->draw_start = -r->line_height / 2 + cub->winsize_y / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + cub->winsize_y / 2;
	if (r->draw_end >= cub->winsize_y)
		r->draw_end = cub->winsize_y - 1;
}

void	ray_helper(t_cub *cub, t_ray *r, int x)
{
	ray_start(cub, r, x);
	ray_dir(cub, r);
	while (!r->hit)
	{
		ray_side(r);
		if (has_hitvoid(cub, r->map_x, r->map_y))
			r->hit = 1;
		else if (has_hitwall(cub, r->map_x, r->map_y))
		{
			ray_hit(cub, r);
			if (cub->map[r->map_x][r->map_y])
				draw_vertical(cub, r, x);
		}
	}
}
