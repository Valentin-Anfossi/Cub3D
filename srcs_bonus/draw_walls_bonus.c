/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 10:25:38 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/19 02:23:04 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_walls(t_cub *cub)
{
	int		x;
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	x = 0;
	while (x < cub->winsize_x - 1)
	{
		ray_helper(cub, r, x);
		x ++;
	}
	free(r);
}
