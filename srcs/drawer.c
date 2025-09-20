/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian					        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:31:08 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/16 11:31:37 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	put_pixel(t_draw *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->data + (y * img->length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// t_draw *draw_circular_background(t_cub *cub)
// {
// 	t_draw	*background;
// 	background = malloc(sizeof(t_draw));
// 	background->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
// 	if (!background->img)
// 	return (NULL);
// 	background->data = mlx_get_data_addr
// 	(background->img, &background->bpp,
// 		&background->length, &background->endian);
// 		if (!background->data)
// 		{
// 			mlx_destroy_image(cub->mlx, background->img);
// 			free(background);
// 			return (NULL);
// 		}
		
		
// 	int horizon;
// 	int y;
// 	float radius;
// 	int x_start;
// 	int x_end;
// 	int x;
// 	horizon = cub->winsize_y/2;
// 	y = horizon;

// 	while(y < horizon)
// 	{
// 		radius = (cub->winsize_y) / (y - horizon + 1);
// 		x_start = cub->winsize_x/2 - radius;
// 		x_end = cub->winsize_x/2 + radius;

// 		if(x_start < 0) x_start = 0;
// 		if(x_end >= cub->winsize_x) x_end = cub->winsize_x -1;
// 		x = x_start;
// 		while (x <= x_end);
// 		{

// 		}
// 	}
// }

t_draw	*draw_background(t_cub *cub)
{
	int		x;
	int		y;
	t_draw	*background;
	float	ratio;

	background = malloc(sizeof(t_draw));
	background->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!background->img)
		return (NULL);
	background->data = mlx_get_data_addr
		(background->img, &background->bpp,
			&background->length, &background->endian);
	if (!background->data)
	{
		mlx_destroy_image(cub->mlx, background->img);
		free(background);
		return (NULL);
	}
	x = 0;
	y = 0;
	ratio = 1;
	while (y < cub->winsize_y)
	{
		while (x < cub->winsize_x)
		{
			if (y < cub->winsize_y / 2)
			{
				ratio = remap(1-(float)y/(cub->winsize_y/2),0,1.25);
				put_pixel(background, x, y, color_mult(cub->ce_color,ratio));
			}
			else
			{
				ratio = remap((float)(y-cub->winsize_y/2)/(cub->winsize_y),0,1.25);
				put_pixel(background, x, y, color_mult(cub->fl_color,ratio));
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (background);
}
