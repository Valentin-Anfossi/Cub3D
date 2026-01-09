/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:07:02 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/09 10:59:29 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	map_init(t_cub *cub)
{
	if (!get_notexpath(cub))
	{
		printf("Error\nTexture North (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if (!get_sotexpath(cub))
	{
		printf("Error\nTexture South (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if (!get_wetexpath(cub))
	{
		printf("Error\nTexture West (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if (!get_eatexpath(cub))
	{
		printf("Error\nTexture East (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	map_init_helper(cub);
}

void	map_init_helper(t_cub *cub)
{
	if (!get_floorclr(cub))
	{
		printf
			("Error\nFloor color (invalid RGB, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if (!get_clclr(cub))
	{
		printf
			("Error\nCeiling color (invalid RGB, absent or wrong order)\n");
		exit_maperror(cub);
	}
	map_parse(get_next_line(cub->map_fd), cub);
}
