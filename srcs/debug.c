/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:22:46 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/27 00:31:07 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	debug_printmap(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_size_x)  // Parcourt les LIGNES (map_size_x)
	{
		j = 0;
		while (j < cub->map_size_y)  // Parcourt les COLONNES (map_size_y)
		{
			if (cub->map[i][j] == WALL)
				printf("⬜");
			else if (cub->map[i][j] == EMPTY)
				printf("⬛");
			else
				printf("🙎");
			j++;
		}
		printf("\n");
		i++;
	}
}

void debug_printPlayer(t_player *p)
{
	printf("Player info :\nPosition :%f,%f\nRotation :%f,%f\n",p->pos->x,p->pos->y,p->dir->x,p->dir->y);
}

void	debug_printcub(t_cub *cub)
{
	printf("== Debug print : Cub struct ==\n");
	if (cub->no_texpath)
		printf("NO: %s\n", cub->no_texpath);
	if (cub->so_texpath)
		printf("SO: %s\n", cub->so_texpath);
	if (cub->we_texpath)
		printf("WE: %s\n", cub->we_texpath);
	if (cub->ea_texpath)
		printf("EA: %s\n", cub->ea_texpath);
	if (cub->fl_texpath)
		printf("FL: %s\n", cub->fl_texpath);
	if (cub->cl_texpath)
		printf("CL: %s\n", cub->cl_texpath);
	printf("Window size X, Y {%d, %d}\n", cub->winsize_x, cub->winsize_y);
	printf("Errnum: %d\nDebug: %d\nMap_fd: %d\n", cub->errnum, cub->debug, cub->map_fd);
	printf("Map size: X, Y {%d, %d}\n", cub->map_size_x, cub->map_size_y);
	printf("Ceilling/Wall colors : 0x%06x, 0x%06x\n", cub->ce_color, cub->fl_color);
	printf("Player position :%f,%f\n",cub->player->pos->x,cub->player->pos->y);
	printf("Map:\n");
	debug_printmap(cub);
	debug_printPlayer(cub->player);

}
