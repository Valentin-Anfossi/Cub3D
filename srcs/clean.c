#include "cub3d.h"

void	free_texture(t_cub *cub)
{
	free(cub->ea_texpath);
	free(cub->we_texpath);
	free(cub->no_texpath);
	free(cub->so_texpath);
	mlx_destroy_image(cub->mlx, cub->buffer->img);
	free(cub->buffer);
	mlx_destroy_image(cub->mlx, cub->texture_no->img);
	free(cub->texture_no);
	mlx_destroy_image(cub->mlx, cub->texture_so->img);
	free(cub->texture_so);
	mlx_destroy_image(cub->mlx, cub->texture_we->img);
	free(cub->texture_we);
	mlx_destroy_image(cub->mlx, cub->texture_ea->img);
	free(cub->texture_ea);
	mlx_destroy_image(cub->mlx, cub->background->img);
	free(cub->background);
	mlx_destroy_image(cub->mlx, cub->buffer_old->img);
	free(cub->buffer_old);
}

void free_player(t_player *p)
{
	free(p->pos);
	free(p->plane);
	free(p->input);
	free(p->dir);
	free(p);
}

void	free_all(t_cub *cub)
{
	int	i;

	i = 0;
	// while (cub->map_str[i])
	// {
	// 	free(cub->map_str[i]);
	// 	i++;
	// }
	free(cub->map_str);
	i = 0;
	while (i < cub->map_size_x)
	{
		free(cub->map[i]);
		i++;
	}
	i = 0;
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_mouse_show(cub->mlx, cub->window);
	free(cub->map);
	free_texture(cub);
	free_player(cub->player);
	free(cub->player_pos);
	free(cub->mlx);
	free(cub);
}

int destroystuff(t_cub *cub) {
    if (cub->buffer) {
        if (cub->buffer->img)
            mlx_destroy_image(cub->mlx, cub->buffer->img);
        // if (cub->buffer->data)
        //     free(cub->buffer->data); // Si tu as alloué data toi-même
        free(cub->buffer);
    }
    // Libère les autres textures (no, so, we, ea) de la même manière
    if (cub->window)
        mlx_destroy_window(cub->mlx, cub->window);
    free(cub->mlx); // Attention : mlx_destroy_display est souvent suffisant
    free(cub);
    exit(0);
}

