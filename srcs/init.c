/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagabundo <vagabundo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/12 00:50:41 by vagabundo        ###   ########.fr       */
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

int	data_img(t_cub *cub)
{
	cub->texture_no->data = mlx_get_data_addr(cub->texture_no->img,
			&cub->texture_no->bpp, &cub->texture_no->length,
			&cub->texture_no->endian);
	cub->texture_so->data = mlx_get_data_addr(cub->texture_so->img,
			&cub->texture_so->bpp, &cub->texture_so->length,
			&cub->texture_so->endian);
	cub->texture_ea->data = mlx_get_data_addr(cub->texture_ea->img,
			&cub->texture_ea->bpp, &cub->texture_ea->length,
			&cub->texture_ea->endian);
	cub->texture_we->data = mlx_get_data_addr(cub->texture_we->img,
			&cub->texture_we->bpp, &cub->texture_we->length,
			&cub->texture_we->endian);
	if (!cub->texture_no->data || !cub->texture_so->data
		|| !cub->texture_ea->data || !cub->texture_we->data)
		return (1);
	return (0);
}

int	init_img(t_cub *cub)
{
	cub->background = draw_background(cub);
	if (!cub->background)
		return (1);
	cub->texture_no = malloc(sizeof(t_draw));
	cub->texture_so = malloc(sizeof(t_draw));
	cub->texture_we = malloc(sizeof(t_draw));
	cub->texture_ea = malloc(sizeof(t_draw));
	cub->texture_no->img = mlx_xpm_file_to_image(cub->mlx, cub->no_texpath,
			&cub->texture_no->width, &cub->texture_no->height);
	cub->texture_so->img = mlx_xpm_file_to_image(cub->mlx, cub->so_texpath,
			&cub->texture_so->width, &cub->texture_so->height);
	cub->texture_we->img = mlx_xpm_file_to_image(cub->mlx, cub->we_texpath,
			&cub->texture_we->width, &cub->texture_we->height);
	cub->texture_ea->img = mlx_xpm_file_to_image(cub->mlx, cub->ea_texpath,
			&cub->texture_ea->width, &cub->texture_ea->height);
	if (!cub->texture_no->img || !cub->texture_so->img
		|| !cub->texture_we->img || !cub->texture_ea->img)
		return (1);
	if (data_img(cub))
		return (1);
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
	if (init_img(cub))
		return (NULL);
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
