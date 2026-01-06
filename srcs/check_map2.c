/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:21:45 by vanfossi/je       #+#    #+#             */
/*   Updated: 2026/01/06 14:50:57 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_maperror(t_cub *c)
{
	int	i;

	i = 0;
	printf("Map error.\n");
	free (c->ea_texpath);
	free (c->we_texpath);
	free (c->no_texpath);
	free (c->so_texpath);
	free (c->player_pos);
	if(c->map_str)
	{
		while (c->map_str[i])
		{
			free(c->map_str[i]);
			i ++;
		}
		free(c->map_str);
	}
	free(c);
	exit(1);
}
