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

#include "./cub3d_bonus.h"

void	put_pixel(t_draw *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->data + (y * img->length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_draw	*init_background(t_cub *cub)
{
	t_draw	*background;

	background = malloc(sizeof(t_draw));
	background->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!background->img)
		return (NULL);
	background->data = (unsigned char *)mlx_get_data_addr
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
