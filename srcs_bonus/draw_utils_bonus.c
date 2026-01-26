/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:21:22 by vanfossi/je       #+#    #+#             */
/*   Updated: 2026/01/06 11:27:28 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dabs(double d)
{
	if (d < 0)
		return (d * -1);
	else
		return (d);
}

int	get_texpixel(int x, int y, t_draw *img)
{
	unsigned char	*pixel;
	int				color;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0x000000);
	pixel = img->data + (y * img->length + x * (img->bpp / 8));
	if (img->endian == 1)
		color = (pixel[0] << 16) | (pixel[1] << 8) | pixel[2] << 0;
	else
		color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0] << 0;
	return (color);
}

float	wall_shade(float dist, int side)
{
	float	clamped_dist;

	if (dist <= 0)
		return (255);
	if (dist >= SHADE_DIST)
		return (0);
	clamped_dist = 1.0f - (dist / SHADE_DIST);
	if (side)
		clamped_dist *= .75;
	return ((int)(clamped_dist * 255.0f));
}

int	has_hitwall(t_cub *cub, int map_x, int map_y)
{
	if (cub->map[map_x][map_y] == WALL)
		return (1);
	else
		return (0);
}

int	has_hitvoid(t_cub *cub, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= cub->map_size_y)
		return (1);
	else if (map_y < 0 || map_y >= cub->map_size_x)
		return (1);
	else
		return (0);
}
