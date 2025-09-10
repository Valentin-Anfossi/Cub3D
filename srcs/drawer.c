#include "./cub3d.h"

void	put_pixel(t_draw *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->data + (y * img->length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_draw	*draw_background(t_cub *cub)
{
	int		x;
	int		y;
	t_draw	*background;

	background = malloc(sizeof(t_draw));
	background->img = mlx_new_image(cub->mlx, cub->winsize_x, cub->winsize_y);
	if (!background->img)
		return (NULL);
	background->data = mlx_get_data_addr
		(background->img, &background->bpp,
			&background->length, &background->endian);
	if (!background->data)
	{
		mlx_destroy_image(cub->mlx, background->img);
		free(background);
		return (NULL);
	}
	x = 0;
	y = 0;
	while (y < cub->winsize_y)
	{
		while (x < cub->winsize_x)
		{
			if (y < cub->winsize_y / 2)
				put_pixel(background, x, y, cub->ce_color);
			else
				put_pixel(background, x, y, cub->fl_color);
			x++;
		}
		x = 0;
		y++;
	}
	return (background);
}
