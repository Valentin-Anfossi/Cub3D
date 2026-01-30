/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/30 04:18:50 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

t_cub	*init(char **argv)
{
	t_cub	*cub;

	cub = create_cub(argv[1]);
	return (cub);
}

int	data_img(t_cub *cub)
{
	cub->texture_no->data = (unsigned char *)mlx_get_data_addr(
			cub->texture_no->img,
			&cub->texture_no->bpp, &cub->texture_no->length,
			&cub->texture_no->endian);
	cub->texture_so->data = (unsigned char *)mlx_get_data_addr(
			cub->texture_so->img,
			&cub->texture_so->bpp, &cub->texture_so->length,
			&cub->texture_so->endian);
	cub->texture_ea->data = (unsigned char *)mlx_get_data_addr(
			cub->texture_ea->img,
			&cub->texture_ea->bpp, &cub->texture_ea->length,
			&cub->texture_ea->endian);
	cub->texture_we->data = (unsigned char *)mlx_get_data_addr(
			cub->texture_we->img,
			&cub->texture_we->bpp, &cub->texture_we->length,
			&cub->texture_we->endian);
	cub->texture_do->data = (unsigned char *)mlx_get_data_addr(
			cub->texture_do->img,
			&cub->texture_do->bpp, &cub->texture_do->length,
			&cub->texture_do->endian);
	if (!cub->texture_no->data || !cub->texture_so->data
		|| !cub->texture_ea->data || !cub->texture_we->data
		|| !cub->texture_do->data)
		return (1);
	return (0);
}

t_draw	*init_buffer(t_cub *cub)
{
	t_draw	*buffer;

	buffer = malloc(sizeof(t_draw));
	buffer->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!buffer->img)
		return (NULL);
	buffer->data = (unsigned char *)mlx_get_data_addr
		(buffer->img, &buffer->bpp,
			&buffer->length, &buffer->endian);
	if (!buffer->data)
	{
		mlx_destroy_image(cub->mlx, buffer->img);
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	init_img(t_cub *cub)
{
	cub->buffer = init_buffer(cub);
	cub->buffer_old = init_buffer(cub);
	cub->background = draw_background(cub);
	if (!cub->buffer)
		return (1);
	cub->texture_no = malloc(sizeof(t_draw));
	cub->texture_so = malloc(sizeof(t_draw));
	cub->texture_we = malloc(sizeof(t_draw));
	cub->texture_ea = malloc(sizeof(t_draw));
	cub->texture_do = malloc(sizeof(t_draw));
	cub->texture_no->img = mlx_xpm_file_to_image(cub->mlx, cub->no_texpath,
			&cub->texture_no->width, &cub->texture_no->height);
	cub->texture_so->img = mlx_xpm_file_to_image(cub->mlx, cub->so_texpath,
			&cub->texture_so->width, &cub->texture_so->height);
	cub->texture_we->img = mlx_xpm_file_to_image(cub->mlx, cub->we_texpath,
			&cub->texture_we->width, &cub->texture_we->height);
	cub->texture_ea->img = mlx_xpm_file_to_image(cub->mlx, cub->ea_texpath,
			&cub->texture_ea->width, &cub->texture_ea->height);
	cub->texture_do->img = mlx_xpm_file_to_image(cub->mlx, cub->do_texpath,
			&cub->texture_do->width, &cub->texture_do->height);
	if (!cub->texture_no->img || !cub->texture_so->img
		|| !cub->texture_we->img || !cub->texture_ea->img || !cub->texture_do)
		return (1);
	if (data_img(cub))
		return (1);
	return (0);
}

int	get_playerinitialdir(t_cub *c)
{
	int	i;

	i = c->map[c->player_pos[0]][c->player_pos[1]];
	if (i == P_NORTH)
		return (90);
	else if (i == P_SOUTH)
		return (260);
	else if (i == P_EAST)
		return (0);
	else
		return (180);
}
