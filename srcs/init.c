/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagabundo <vagabundo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/11 01:32:15 by vagabundo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_cub	*init(int argc, char **argv)
{
	t_cub	*cub;
	int		test_fd;

	(void)argc;
	(void)argv;
	if (argc != 2)
		return (0);
	if (!argv[1])
		return (0);
	test_fd = open(argv[1], O_RDONLY);
	if (test_fd < 0)
		return (NULL);
	close(test_fd);
	cub = create_cub(argv[1]);
	return (cub);
}

int	init_img(t_cub *cub)
{
	cub->background = draw_background(cub);
	if (!cub->background->img)
	{
		free(cub->background->img);
		return (1);
	}
	return (0);
}

t_cub	*create_cub(char *path)
{
	t_cub	*cub;

	(void)path;
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->mlx = mlx_init();
	cub->winsize_x = 1800;
	cub->winsize_y = 980;
	cub->map_fd = open(path, O_RDONLY);
	cub->map_str = NULL;
	cub->errnum = 0;
	cub->debug = 0;
	cub->no_texpath = NULL;
	cub->so_texpath = NULL;
	cub->we_texpath = NULL;
	cub->ea_texpath = NULL;
	cub->ce_color = 0;
	cub->fl_color = 0;
	map_init(cub);
	init_img(cub);
	cub->window = mlx_new_window
		(cub->mlx, cub->winsize_x, cub->winsize_y, "Cub3d");
	if (!cub->window)
	{
		free(cub);
		return (NULL);
	}
	debug_printcub(cub);
	return (cub);
}

void	init_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map_size_y)
	{
		while (x < cub->map_size_x)
		{
			cub->map[y][x] = 0;
			x ++;
		}
		x = 0;
		y ++;
	}
}
