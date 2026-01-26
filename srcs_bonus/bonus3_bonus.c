/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:00:52 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/08 22:33:54 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

t_minimap	*malloc_minimap(void)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->map_sizex = 0;
	minimap->map_sizey = 0;
	minimap->x = 0;
	minimap->y = 0;
	minimap->xpos = 0;
	minimap->ypos = 0;
	minimap->xmap = 0;
	minimap->ymap = 0;
	minimap->zoom = 0;
	return (minimap);
}

void	draw_hline_w(t_cub *cub, int x1, int x2, int y)
{
	while (x1 <= x2)
	{
		put_pixel(cub->buffer, x1, y, create_argb(1, 255, 255, 255));
		x1++;
	}
}
