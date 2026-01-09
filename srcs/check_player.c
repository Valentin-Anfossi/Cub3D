/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:12:23 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/09 10:56:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(t_cub *cub)
{
	int		i;
	int		j;
	char	c;
	int		p;

	i = 0;
	p = 0;
	while (cub->map_str[i])
	{
		j = 0;
		while (cub->map_str[i][j])
		{
			c = cub->map_str[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				p ++;
			j ++;
		}
		i ++;
	}
	if (p != 1)
	{
		printf("Error\nInvalid player count.\n");
		return (0);
	}
	return (1);
}
