/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:54:08 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/30 15:03:12 by vanfossi         ###   ########.fr       */
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
