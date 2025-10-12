/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:10:11 by vagabundo         #+#    #+#             */
/*   Updated: 2025/10/12 09:08:54 by vanfossi         ###   ########.fr       */
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
