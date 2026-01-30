/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 04:46:49 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/30 15:01:48 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	event_interact(t_cub *cub)
{
	t_v2	f;

	f.x = cub->player->pos->x + cub->player->dir->x;
	f.y = cub->player->pos->y + cub->player->dir->y;
	if (cub->map[(int)f.x][(int)f.y] == DOOR_C)
	{
		cub->map[(int)f.x][(int)f.y] = DOOR_O;
	}
	else if (cub->map[(int)f.x][(int)f.y] == DOOR_O)
	{
		if (!((int)f.x == (int)cub->player->pos->x && (int)f.y
				== (int)cub->player->pos->y))
		{
			cub->map[(int)f.x][(int)f.y] = DOOR_C;
		}
	}
}
