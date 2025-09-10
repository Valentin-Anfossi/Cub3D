/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagabundo <vagabundo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/11 01:30:37 by vagabundo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	refresh(t_cub *cub)
{
	printf("%d\n", cub->errnum);
	return (cub->errnum);
}

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		destroystuff(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init(argc, argv);
	if (!cub || cub->errnum)
		error_exit(cub);
	mlx_hook(cub->window, 17, 1L << 17, destroystuff, cub);
	mlx_hook(cub->window, KeyPress, KeyPressMask, handle_key, cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->background->img, 0, 0);
	mlx_loop(cub->mlx);
	free_all(cub);
}
