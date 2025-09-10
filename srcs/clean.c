#include "cub3d.h"

void	free_texture(t_cub *cub)
{
	free(cub->ea_texpath);
	free(cub->we_texpath);
	free(cub->no_texpath);
	free(cub->so_texpath);
	mlx_destroy_image(cub->mlx, cub->background->img);
	free(cub->background);
}

void	free_all(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map_str[i])
	{
		free(cub->map_str[i]);
		i++;
	}
	free(cub->map_str);
	i = 0;
	while (i < cub->map_size_y)
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
	free_texture(cub);
	free(cub->mlx);
	free(cub);
}

int	destroystuff(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	mlx_loop_end(cub->mlx);
	return (0);
}

