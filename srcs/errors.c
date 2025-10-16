/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:57:47 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/16 23:07:05 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void error_exit(t_cub *c)
{
	// free_all(c);
	if(c && c->errnum == 1)
	{
		printf("Cub3D ERROR : %d (cub3d -m for help)\n",c->errnum);
		exit (c->errnum);
	}
	else
	{
		printf("Cub3D INIT ERROR\n");
		exit (1);
	}
}
