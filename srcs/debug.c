/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:22:46 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/10 18:51:32 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void debug_printmap(t_cub *cub)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < cub->map_size_y)
    {
        while(j < cub->map_size_x)
        {
            if(cub->map[i][j] == WALL)
                printf("⬜");
            else if(cub->map[i][j] == EMPTY)
                printf("⬛");
            else
                printf("🙎");
            j ++;
        }
        i ++;
        printf("\n");
        j = 0;
    }
}

void debug_printcub(t_cub *cub)
{
	printf("== Debug print : Cub struct ==\n");
	if(cub->no_texpath)
		printf("NO: %s",cub->no_texpath);
	if(cub->so_texpath)
		printf("SO: %s",cub->so_texpath);
	if(cub->we_texpath)
		printf("WE: %s",cub->we_texpath);
	if(cub->ea_texpath)
		printf("EA: %s",cub->ea_texpath);
	printf("Window size X,Y {%d,%d}\n",cub->winsize_x,cub->winsize_x);
	printf("Errnum: %d\nDebug: %d\nMap_fd: %d\n",cub->errnum,cub->debug,cub->map_fd);
	printf("Map size: X,Y {%d,%d}\n",cub->map_size_x,cub->map_size_y);
	printf("Ceilling/Wall colors : 0x%06x,0x%06x\n",cub->ce_color,cub->fl_color);
	printf("Map:\n");
    debug_printmap(cub);
}