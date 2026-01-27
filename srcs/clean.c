/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 08:31:24 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/27 14:55:17 by vanfossi         ###   ########.fr       */
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

void	free_player(t_player *p)
{
	free(p->pos);
	free(p->plane);
	free(p->input);
	free(p->dir);
	free(p);
}

void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map_size_y)
	{
		free(cub->map[i]);
		i++;
	}
	i = 0;
	free(cub->map_str);
	free(cub->map);
}

void	free_all(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	free_texture(cub);
	free_player(cub->player);
	free_map(cub);
	free(cub->player_pos);
	mlx_destroy_window(cub->mlx, cub->window);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
}

int	destroystuff(t_cub *cub)
{
	(void)cub;
	mlx_loop_end(cub->mlx);
	return (0);
}
