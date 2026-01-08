/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 02:24:11 by vanfossi/je       #+#    #+#             */
/*   Updated: 2025/10/19 02:24:14 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_sizex(t_cub *cub)
{
	int	i;
	int	j;
	int	size_x;

	i = 0;
	j = 0;
	size_x = 0;
	while (cub->map_str[i])
	{
		j = 0;
		while (cub->map_str[i][j])
			j ++;
		if (j > size_x)
			size_x = j;
		i ++;
	}
	return (size_x);
}
