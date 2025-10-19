/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:30:17 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/19 02:23:38 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		destroystuff(cub);
	if (keycode == KEY_UP)
		cub->player->input->x += 1;
	if (keycode == KEY_DOWN)
		cub->player->input->x -= 1;
	if (keycode == KEY_LEFT)
		cub->player->input->y += 1;
	if (keycode == KEY_RIGHT)
		cub->player->input->y -= 1;
	if (keycode == KEY_STLEFT)
		cub->player->input->z += 1;
	if (keycode == KEY_STRIGHT)
		cub->player->input->z -= 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_cub *cub)
{
	if (keycode == KEY_UP)
		cub->player->input->x -= 1;
	if (keycode == KEY_DOWN)
		cub->player->input->x += 1;
	if (keycode == KEY_LEFT)
		cub->player->input->y -= 1;
	if (keycode == KEY_RIGHT)
		cub->player->input->y += 1;
	if (keycode == KEY_STLEFT)
		cub->player->input->z -= 1;
	if (keycode == KEY_STRIGHT)
		cub->player->input->z += 1;
	return (0);
}

int	handle_mouse(t_cub *cub)
{
	(void)cub;
	return (0);
}
