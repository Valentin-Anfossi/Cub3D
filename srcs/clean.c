/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 08:31:24 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 23:02:26 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_cub *cub)
{
	free(cub->ea_texpath);
	free(cub->we_texpath);
	free(cub->no_texpath);
	free(cub->so_texpath);
	mlx_destroy_image(cub->mlx, cub->buffer->img);
	free(cub->buffer);
	mlx_destroy_image(cub->mlx, cub->texture_no->img);
	free(cub->texture_no);
	mlx_destroy_image(cub->mlx, cub->texture_so->img);
	free(cub->texture_so);
	mlx_destroy_image(cub->mlx, cub->texture_we->img);
	free(cub->texture_we);
	mlx_destroy_image(cub->mlx, cub->texture_ea->img);
	free(cub->texture_ea);
	mlx_destroy_image(cub->mlx, cub->background->img);
	free(cub->background);
	mlx_destroy_image(cub->mlx, cub->buffer_old->img);
	free(cub->buffer_old);
}

void free_player(t_player *p)
{
	free(p->pos);
	free(p->plane);
	free(p->input);
	free(p->dir);
	free(p);
}

void free_mapstr(t_cub *cub)
{
	free(cub->map);
}

void	free_all(t_cub *cub)
{
	int	i;

	i = 0;
	mlx_loop_end(cub->mlx);
	free(cub->map_str);
	i = 0;
	while (i < cub->map_size_x)
	{
		free(cub->map[i]);
		i++;
	}
	i = 0;
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_mouse_show(cub->mlx, cub->window);
	free_texture(cub);
	free_player(cub->player);
	free_mapstr(cub);
	free(cub->player_pos);
	mlx_destroy_window(cub->mlx, cub->window);
	// mlx_destroy_image(cub->mlx,cub->buffer->img);
	free(cub->mlx);
	free(cub);
}

int destroystuff(t_cub *cub) {
	(void)cub;
	mlx_loop_end(cub->mlx);
    // if (cub->buffer) {
    //     if (cub->buffer->img)
    //         mlx_destroy_image(cub->mlx, cub->buffer->img);
    //     // free(cub->buffer);
    // }
    // if (cub->window)
	return (0);
}
