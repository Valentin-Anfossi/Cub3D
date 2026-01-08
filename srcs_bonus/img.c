/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:10:11 by vagabundo         #+#    #+#             */
/*   Updated: 2025/10/19 02:23:42 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	start_window(t_cub *cub)
{
	ft_printf("start window...\n");
	cub->window = mlx_new_window
		(cub->mlx, cub->winsize_x, cub->winsize_y, "cub3d");
	if (!cub->window)
		return (ft_printf("\nWindow error"), 1);
	return (ft_printf ("\tOK\n"), 0);
}
