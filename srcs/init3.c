/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 09:10:15 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 09:10:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_shadelut(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(x < 256)
	{
		while (y < 256)
		{
			cub->shade_lut[x][y] = (int)((x * y) / 255.0f);
			y ++;
		}
		y = 0;
		printf("\n");
		x ++;
	}
}

void	init_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->map_size_x)
	{
		y = 0;
		while (y < cub->map_size_y)
		{
			cub->map[x][y] = 0;
			y ++;
		}
		x ++;
	}
}