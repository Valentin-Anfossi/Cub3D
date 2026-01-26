/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:19:47 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/08 18:43:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

void	draw_square(t_cub *cub, int x0, int y0, int size)
{
	int	y;

	y = y0;
	while (y < (y0 + size))
	{
		draw_hline(cub, x0, x0 + size, y);
		y ++;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_minimap	*mi;

	mi = cub->minimap;
	mi->xpos = cub->player->pos->x;
	mi->ypos = cub->player->pos->y;
	if (cub->map_fullscreen)
	{
		mi->zoom = .05;
		mi->map_sizey = cub->winsize_y;
		mi->map_sizex = cub->winsize_x;
	}
	else
	{
		mi->zoom = .035;
		mi->map_sizey = cub->winsize_y / 3;
		mi->map_sizex = cub->winsize_y / 3;
		draw_square(cub, 0, 0, mi->map_sizey);
		draw_square(cub, 3, 3, mi->map_sizey -6);
	}
	draw_minimap_helper(cub, mi);
}

void	draw_minimap_helper(t_cub *cub, t_minimap *mi)
{
	int	wall;

	mi->y = 0;
	mi->x = 0;
	while (mi->y <= mi->map_sizex)
	{
		mi->x = 0;
		while (mi->x <= mi->map_sizey)
		{
			mi->xmap = mi->xpos + (mi->x - ((mi->map_sizey) / 2)) * mi->zoom;
			mi->ymap = mi->ypos + (mi->y - ((mi->map_sizex) / 2)) * mi->zoom;
			if (mi->xmap < cub->map_size_y && mi->xmap
				>= 0 && mi->ymap < cub->map_size_x && mi->ymap >= 0)
			{
				wall = cub->map[(int)mi->xmap][(int)mi->ymap];
				if (wall == 1)
					put_pixel(cub->buffer, mi->y, mi->x,
						create_argb(1, 0, 255, 0));
			}
			mi->x ++;
		}
		mi->y ++;
	}
	draw_minimap_player(cub, mi);
}

void	draw_line(t_v2 p1, t_v2 p2, t_cub *cub, int norminette)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	step;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = p1.x;
	y = p1.y;
	while (norminette <= step)
	{
		put_pixel(cub->buffer, x, y, create_argb(1, 255, 64, 64));
		x = x + dx;
		y = y + dy;
		norminette ++;
	}
}

void	draw_minimap_player(t_cub *cub, t_minimap *mi)
{
	t_v2	p0;
	t_v2	p1;

	p0.x = (mi->map_sizex / 2);
	p0.y = (mi->map_sizey / 2);
	p1.x = p0.x + (12.5 *(cub->player->dir->y));
	p1.y = p0.y + (12.5 *(cub->player->dir->x));
	draw_circle(cub, (mi->map_sizex) / 2, (mi->map_sizey) / 2, 10);
	draw_line(p0, p1, cub, 0);
}
