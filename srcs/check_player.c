/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:12:23 by vanfossi          #+#    #+#             */
/*   Updated: 2025/12/08 14:12:38 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int playerdouble_check(t_cub *c)
{
    int x;
    int y;

    x = 0;
    y = 0;
    return (1);
}

int playeronedge_check(t_cub *c)
{
    return (1);
}

int player_check(t_cub *c)
{
	if(!playerdouble_check(c))
		return (0);
    if(!playeronedge_check(c))
        return (0);
}