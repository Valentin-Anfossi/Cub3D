/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/11 04:57:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_cub *init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_cub *cub;

	int test_fd;
	// if(argc != 2)
	// 	return (0);
	// if(!argv || !argv[1])
	// 	return (0);
	test_fd = open("./maps/01.cub",O_RDONLY);
	if(test_fd < 0)
		return (NULL);
	close(test_fd);
	cub = create_cub("./maps/01.cub");
	return (cub);
}

t_cub *create_cub(char *path)
{
	t_cub *cub;

	(void)path;
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map_fd = open(path,O_RDONLY);
	cub->errnum = 0;
	cub->debug = 0;
	cub->no_texpath = NULL;
	cub->so_texpath = NULL;
	cub->we_texpath = NULL;
	cub->ea_texpath = NULL;
	map_init(cub);
	debug_printcub(cub);

	return (cub);
}

void init_map(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;

	while(y < cub->map_size_y)
	{
		while(x < cub->map_size_x)
		{
			cub->map[y][x] = 0;
			x ++;
		}
		x = 0;
		y ++;
	}
}