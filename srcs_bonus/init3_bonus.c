/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 09:10:15 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/30 15:20:36 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_shadelut(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 256)
	{
		while (y < 256)
		{
			cub->shade_lut[x][y] = (int)((x * y) / 255.0f);
			y ++;
		}
		y = 0;
		x ++;
	}
}

void	init_map(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map_size_y)
	{
		x = 0;
		while (x < cub->map_size_x)
		{
			cub->map[y][x] = 0;
			x ++;
		}
		y ++;
	}
}

int	malloc_textures(t_cub *cub)
{
	cub->texture_no = malloc(sizeof(t_draw));
	cub->texture_so = malloc(sizeof(t_draw));
	cub->texture_we = malloc(sizeof(t_draw));
	cub->texture_ea = malloc(sizeof(t_draw));
	cub->texture_do = malloc(sizeof(t_draw));
	if (!cub->texture_no || !cub->texture_do || !cub->texture_ea
		|| !cub->texture_so || !cub->texture_we)
		return (0);
	return (1);
}
