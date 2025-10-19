/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:22:29 by vanfossi/je       #+#    #+#             */
/*   Updated: 2025/10/19 02:22:40 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bk	init_bkstruct(void)
{
	t_bk	bk;

	bk.x = 0;
	bk.y = 0;
	bk.rt = 1;
	return (bk);
}

float	normimerde(t_cub *c, int bky)
{
	float	re;

	re = (float)(bky - c->winsize_y / 2) / (c->winsize_y);
	re = remap(re, 0, 1.25);
	return (re);
}

t_draw	*draw_background(t_cub *cub)
{
	t_bk	bk;
	t_draw	*bg;

	bg = init_background(cub);
	bk = init_bkstruct();
	while (bk.y < cub->winsize_y)
	{
		while (bk.x < cub->winsize_x)
		{
			if (bk.y < cub->winsize_y / 2)
			{
				bk.rt = remap(1 - (float)bk.y / (cub->winsize_y / 2), 0, 1.25);
				put_pixel(bg, bk.x, bk.y, color_mult(cub->ce_color, bk.rt));
			}
			else
			{
				bk.rt = normimerde(cub, bk.y);
				put_pixel(bg, bk.x, bk.y, color_mult(cub->fl_color, bk.rt));
			}
			bk.x++;
		}
		bk.x = 0;
		bk.y++;
	}
	return (bg);
}
