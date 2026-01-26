/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:57:47 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/04 11:35:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	errormap_exit(t_cub *c)
{
	free(c);
	exit(1);
}

void	error_exit(t_cub *c)
{
	if (c && c->errnum == 1)
	{
		printf("Cub3D ERROR : %d (cub3d -m for help)\n", c->errnum);
		exit (c->errnum);
	}
	else
	{
		printf("Cub3D Exiting...\n");
		exit (1);
	}
}
