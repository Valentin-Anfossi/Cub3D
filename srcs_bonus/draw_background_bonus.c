/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:22:29 by vanfossi/je       #+#    #+#             */
/*   Updated: 2026/01/29 00:01:46 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_bk	init_bkstruct(void)
{
	t_bk	bk;

	bk.x = 0;
	bk.y = 0;
	bk.rt = 1;
	return (bk);
}

float	drawbk_helper(t_cub *c, int bky)
{
	float	re;

	re = (float)(bky - c->winsize_y / 2) / (c->winsize_y);
	re = remap(re, 0, 1);
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
				bk.rt = remap(1 - (float)bk.y / (cub->winsize_y / 2), 0, 1);
				put_pixel(bg, bk.x, bk.y, color_mult(cub->ce_color, bk.rt));
			}
			else
			{
				bk.rt = drawbk_helper(cub, bk.y);
				put_pixel(bg, bk.x, bk.y, color_mult(cub->fl_color, bk.rt));
			}
			bk.x++;
		}
		bk.x = 0;
		bk.y++;
	}
	return (bg);
}
