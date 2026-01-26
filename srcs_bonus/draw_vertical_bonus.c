/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:22:45 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/09 10:34:15 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_vside(t_cub *cub, t_ray *r, t_vert *v)
{
	if (r->side == 0)
	{
		if (r->step_x == -1)
			v->cur_tex = cub->texture_so;
		else
			v->cur_tex = cub->texture_no;
	}
	else
	{
		if (r->step_y == -1)
			v->cur_tex = cub->texture_ea;
		else
			v->cur_tex = cub->texture_we;
	}
	if (r->side == 0)
		v->wall_x = cub->player->pos->y + r->perpwall_dist * r->raydir_y;
	else
		v->wall_x = cub->player->pos->x + r->perpwall_dist * r->raydir_x;
	v->wall_x -= floor(v->wall_x);
}

void	draw_vertical(t_cub *cub, t_ray *r, int x)
{
	t_vert	*v;

	v = malloc(sizeof(t_vert));
	draw_vside(cub, r, v);
	v->tex_x = (int)(v->wall_x * (float)v->cur_tex->width);
	if (r->side == 0 && r->raydir_x > 0)
		v->tex_x = v->cur_tex->width - v->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		v->tex_x = v->cur_tex->width - v->tex_x - 1;
	v->step = 1.0 * v->cur_tex->height / r->line_height;
	v->tex_pos = (r->draw_start - (cub->winsize_y / 2) + r->line_height / 2)
		* v->step;
	v->shade = wall_shade(r->perpwall_dist, r->side);
	while (r->draw_start < r->draw_end)
	{
		v->tex_y = (int)v->tex_pos & (v->cur_tex->height - 1);
		v->tex_pos += v->step;
		put_pixel(cub->buffer, x, r->draw_start,
			color_mult_fast(get_texpixel(v->tex_x, v->tex_y, v->cur_tex),
				v->shade, cub));
		r->draw_start ++;
	}
	free(v);
}
