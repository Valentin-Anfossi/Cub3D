/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:46:55 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 15:12:54 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_foremptylines(t_cub *cub)
{
    int i;

    i = 0;
    while(cub->map_str[i])
    {
        if(is_line_empty(cub->map_str[i]))
            return (0);
        i ++;
    }
    return (1);
}

int check_ismapclosed(t_cub *cub)
{
    int x;
    int y;
    char **m;

    x = 0;
    y = 0;
    m = cub->map_str;
    while(y < cub->map_size_y)
    {
        while(x < cub->map_size_x)
        {
            if(!m[y] || !m[y][x])
                break;
            if(is_notwall(m[y][x]))
            {
                if (is_empty(cub, x, y))
                    return (0);
            }
            x ++;
        }
        x = 0;
        y ++;
    }
    return (1);
}

int is_empty(t_cub *c,int x,int y)
{
    char **m;

    m = c->map_str;
    if (x == 0 || y == 0 || y == c->map_size_y - 1)
        return (1);
    if(ft_isspace(m[y-1][x]) || ft_isspace(m[y+1][x]) || ft_isspace(m[y][x-1])
         || ft_isspace(m[y][x+1]))
        return (1);
    return (0);
}

int is_notwall(int c)
{
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
        return (1);
    return (0);
}
