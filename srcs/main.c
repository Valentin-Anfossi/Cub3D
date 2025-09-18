/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/18 10:58:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- mettre en place la FOV
- savoir l'orientation du perso (si y perso < a y mur = no texture ?)
- redimensionner les texture en fonction du perso
*/
#include "cub3d.h"

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		destroystuff(cub);
	return (0);
}

void copy_buffer(t_draw *dest, const t_draw *src, t_cub *cub)
{
	ft_memcpy(dest->data, src->data, (cub->winsize_x * cub->winsize_y) *sizeof(int));
}

int render_loop(t_cub *cub)
{
	if(!cub->mlx)
		return (0);
	
	ft_memset(cub->buffer->data,0,cub->winsize_x * cub ->winsize_y * sizeof(int));
	copy_buffer(cub->buffer, cub->buffer_old, cub);
	draw_walls(cub);
	mlx_put_image_to_window(cub->mlx,cub->window,cub->buffer->img,0,0);
	// cub->buffer_old = cub->buffer;
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init(argc, argv);
	if (!cub || cub->errnum)
		error_exit(cub);
	mlx_hook(cub->window, 17, 1L << 17, destroystuff, cub);
	mlx_hook(cub->window, KeyPress, KeyPressMask, handle_key, cub);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_no->img, 100, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_so->img, 200, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_we->img, 300, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_ea->img, 400, cub->winsize_y / 2.05);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_loop(cub->mlx);

	free_all(cub);
}
