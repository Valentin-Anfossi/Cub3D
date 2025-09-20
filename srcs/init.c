/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:13 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/20 07:38:55 by vanfossi         ###   ########.fr       */
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

t_draw *init_buffer(t_cub *cub)
{
	t_draw	*buffer;

	buffer = malloc(sizeof(t_draw));
	buffer->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!buffer->img)
		return (NULL);
	buffer->data = mlx_get_data_addr
		(buffer->img, &buffer->bpp,
			&buffer->length, &buffer->endian);
	if (!buffer->data)
	{
		mlx_destroy_image(cub->mlx, buffer->img);
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	init_img(t_cub *cub)
{
	cub->buffer = init_buffer(cub);
	cub->buffer_old = init_buffer(cub);
	cub->background = draw_background(cub);
	if (!cub->buffer)
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

int get_playerInitialDir(t_cub *c)
{
	int i;

	i = c->map[c->player_pos[0]][c->player_pos[1]];
	if (i == P_NORTH)
		return (90);
	else if (i == P_SOUTH)
		return (260);
	else if (i == P_EAST)
		return (0);
	else
		return (180);
}

t_player *player_init(t_cub *cub)
{
	t_player *p;

	p = malloc(sizeof(t_player));
	p->pos = malloc(sizeof(t_v2));
	p->plane = malloc(sizeof(t_v2));
	p->input = malloc(sizeof(t_v2));
	p->dir = malloc(sizeof(t_v2));
	printf("playerpos:%d,%d\n",cub->player_pos[0],cub->player_pos[1]);
	// p->dir =  get_playerInitialDir(cub->map[cub->player_pos[0]][cub->player_pos[1]]);
	p->dir->x = 0.0;
	p->dir->y = 1.0;
	p->pos->x = (float)cub->player_pos[0]+.5;
	p->pos->y = (float)cub->player_pos[1]+.5;
	p->plane->x = 0.66;
	p->plane->y = 0.0;
	p->speed = .05;
	p->rot_speed = .025;
	p->input->x = 0;
	p->input->y = 0;
	return (p);
	
}

t_cub	*create_cub(char *path)
{
	t_cub	*cub;

	(void)path;
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->mlx = mlx_init();
	cub->winsize_x = WIN_SIZEX;
	cub->winsize_y = WIN_SIZEY;
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
	cub->player_pos = malloc(sizeof(int)*2);
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
	cub->player = player_init(cub);
	gettimeofday(&(cub->start_time), NULL);
	debug_printcub(cub);
	return (cub);
}

void	init_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->map_size_x)
	{
		y = 0;
		while (y < cub->map_size_y)
		{
			cub->map[x][y] = 0;
			y ++;
		}
		x ++;
	}
}
