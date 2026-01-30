/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:19:47 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/30 16:03:14 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

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

void	draw_minimap_helper2(t_cub *cub, t_minimap *mi)
{
	int	wall;

	wall = cub->map[(int)mi->xmap][(int)mi->ymap];
	if (wall == 1)
		put_pixel(cub->buffer, mi->y, mi->x,
			create_argb(1, 200, 200, 200));
	else if (wall == DOOR_C)
		put_pixel(cub->buffer, mi->y, mi->x,
			create_argb(1, 0, 0, 255));
	else if (wall == DOOR_O)
		put_pixel(cub->buffer, mi->y, mi->x,
			create_argb(1, 0, 255, 0));
}

void	draw_minimap_helper(t_cub *cub, t_minimap *mi)
{
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
				draw_minimap_helper2(cub, mi);
			}
			mi->x ++;
		}
		mi->y ++;
	}
	draw_minimap_player(cub, mi);
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
