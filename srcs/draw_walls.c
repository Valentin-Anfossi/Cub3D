/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 08:54:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/17 09:59:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_walls(t_cub *cub)
{
	t_draw *walls;

	walls = malloc(sizeof(t_draw));
	walls->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if(!walls->img)
		return ;
	walls->data = mlx_get_data_addr(walls->img, &walls->bpp, &walls->length,
			&walls->endian);
	if(!walls->data)
	{
		mlx_destroy_image(cub->mlx, walls->img);
		free(walls);
		return ;
	}
	int x;
	int y;
	
	x = 0;
	y = 0;
	while(y < cub->winsize_y)
	{
		while(x < cub->winsize_x)
		{
			
			// mlx_pixel_put(cub->mlx,cub->window,x,y,create_argb(1,60,0,0));
			put_pixel(walls,x,y,create_argb(0,50,0,0));
			x ++;
		}
		x = 0;
		y ++;
	}
	cub->walls = walls;
	// ft_memset(cub->walls->data,0,cub->winsize_x * cub->winsize_y * sizeof(int));
	(void)cub;
}

void	draw_walls(t_cub *cub)
{
	(void)cub;
}