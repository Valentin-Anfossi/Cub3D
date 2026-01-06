/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 16:04:26 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//WALLCOLLISIONS ✅
//MINIMAP ✅
//DOORS
//SPRITES 
//ROTATEMOUSE ✅

void	copy_buffer(t_draw *dest, const t_draw *src, t_cub *cub)
{
	ft_memcpyfast(dest->data, src->data, (cub->winsize_x * cub->winsize_y)
		* sizeof(int));
}

void	cap_fps(t_cub *cub)
{
	double	sleep_time;

	if (cub->delta_time < 1000 / TARGET_FPS)
	{
		sleep_time = ((1000 / TARGET_FPS) - cub->delta_time) * 1000;
		usleep(sleep_time);
	}
}

int	render_loop(t_cub *cub)
{

	if (!cub->mlx)
		return (0);
	copy_buffer(cub->buffer, cub->background, cub);
	draw_walls(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->buffer->img, 0, 0);
	move_player(cub);
	mouse_rotate(cub);
	cap_fps(cub);
	
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	file_check(argc,argv);
	cub = init(argv);
	if (!cub || cub->errnum != 0)
		error_exit(cub);
	debug_printcub(cub);
	mlx_hook(cub->window, 17, 1L << 17, destroystuff, cub);
	mlx_hook(cub->window, KeyPress, KeyPressMask, handle_key, cub);
	mlx_hook(cub->window, KeyRelease, KeyRelease, handle_keyrelease, cub);
	mlx_do_key_autorepeatoff(cub->mlx);
	set_playerinitialrot(cub);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_loop(cub->mlx);
	mlx_do_key_autorepeaton(cub->mlx);
	free_all(cub);
	return (0);
}
