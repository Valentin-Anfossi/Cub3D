/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:21:45 by vanfossi/je       #+#    #+#             */
/*   Updated: 2025/10/19 02:21:48 by vanfossi/je      ###   ########.fr       */
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
	while (i < c->map_size_x)
	{
		free(c->map_str[i]);
		i ++;
	}
	free(c->map_str);
	free(c);
	exit(1);
}
