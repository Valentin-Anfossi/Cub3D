/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:22:46 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/11 09:54:03 by vanfossi         ###   ########.fr       */
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
			else if (cub->map[i][j] == DOOR_H || cub->map[i][j] == DOOR_V)
				printf("🚪");
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
	printf("Window size X, Y {%d, %d}\n", cub->winsize_x, cub->winsize_y);
	printf("Errnum: %d\nDebug: %d\nMap_fd: %d\n", cub->errnum, cub->debug, cub->map_fd);
	printf("Map size: X, Y {%d, %d}\n", cub->map_size_x, cub->map_size_y);
	printf("Ceilling/Wall colors : 0x%06x, 0x%06x\n", cub->ce_color, cub->fl_color);
	printf("Player position :%f,%f\n",cub->player->pos->x,cub->player->pos->y);
	printf("Map:\n");
	debug_printmap(cub);
	debug_printPlayer(cub->player);

}
void draw_debug(t_cub *cub) 
{
    double frameTime;

    cub->old_time = cub->time;
    gettimeofday(&(cub->time), NULL);
    frameTime = (cub->time.tv_sec - cub->old_time.tv_sec) +
                (cub->time.tv_usec - cub->old_time.tv_usec) * 1e-6;
	cub->delta_time = frameTime * 1000;
	float fps = (1.0 / frameTime);
	char str[320];
	if(fps > TARGET_FPS)
		fps = TARGET_FPS;
	sprintf(str,"FPS :%.0f \n Player pos : %f %f dir : %f %f",fps,cub->player->pos->x,cub->player->pos->y,cub->player->dir->x,cub->player->dir->y); //ATTENTION C PAS AUTORISE (JE CROIS)
	mlx_string_put(cub->mlx,cub->window,0,cub->winsize_y,create_argb(1,255,255,255),str);
}