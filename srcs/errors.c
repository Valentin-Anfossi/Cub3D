/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:57:47 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/19 02:23:30 by vanfossi/je      ###   ########.fr       */
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
		printf("Cub3D Erreur initialisation\n");
		exit (1);
	}
}
