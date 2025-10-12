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

t_draw *init_background(t_cub *cub)
{
	t_draw *background;

	background = malloc(sizeof(t_draw));
	background->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!background->img)
		return (NULL);
	background->data = (unsigned char*)mlx_get_data_addr
		(background->img, &background->bpp,
			&background->length, &background->endian);
	if (!background->data)
	{
		mlx_destroy_image(cub->mlx, background->img);
		free(background);
		return (NULL);
	}
	return (background);
}

t_bk init_bkstruct(void)
{
	t_bk bk;

	bk.x = 0;
	bk.y = 0;
	bk.ratio = 1;
	return (bk);
}

t_draw	*draw_background(t_cub *cub)
{
	t_bk 	bk;
	t_draw	*background;

	background = init_background(cub);
	bk = init_bkstruct();
	while (bk.y < cub->winsize_y)
	{
		while (bk.x < cub->winsize_x)
		{
			if (bk.y < cub->winsize_y / 2)
			{
				bk.ratio = remap(1-(float)bk.y/(cub->winsize_y/2),0,1.25);
				put_pixel(background, bk.x, bk.y, color_mult(cub->ce_color,bk.ratio));
			}
			else
			{
				bk.ratio = remap((float)(bk.y-cub->winsize_y/2)/(cub->winsize_y),0,1.25);
				put_pixel(background, bk.x, bk.y, color_mult(cub->fl_color,bk.ratio));
			}
			bk.x++;
		}
		bk.x = 0;
		bk.y++;
	}
	return (background);
}
