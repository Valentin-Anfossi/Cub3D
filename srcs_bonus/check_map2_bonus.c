/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:21:45 by vanfossi/je       #+#    #+#             */
/*   Updated: 2026/01/30 04:10:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	exit_maperror(t_cub *c)
{
	int	i;

	i = 0;
	free (c->ea_texpath);
	free (c->we_texpath);
	free (c->no_texpath);
	free (c->so_texpath);
	free (c->do_texpath);
	free (c->player_pos);
	if (c->map_str)
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
