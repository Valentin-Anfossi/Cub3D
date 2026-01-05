/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:46:55 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/05 15:28:45 by vanfossi         ###   ########.fr       */
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
        printf("%s",cub->map_str[i]);
        i ++;
    }
    return (1);
}
//1ere ligne cest que des 1 ou des espaces
//derniere ligne pareil
//si ya un espace ou fin de ligne a gauche ou a droite, c'est forcement un 1

int check_ismapclosed(t_cub *cub)
{
    int x;
    int y;
   // int c;
    
    x = 0;
    y = 0;
    // while(y < cub->map_size_y)
    // {
    //     if (y == 0 && (!ft_isspace(cub->map_str[y][x]) || cub->map_str[y][x] != '1'))
    //         return (0);
    //     while(cub->map[y][x])
    //     {
    //         c = cub->map[y][x];
    //         if (c == '0')
    //         {
    //             if(x == 0 || !ft_isspace(cub->map[y][x-1]) || cub->map[y][x+1])
    //         }
    //     }
    //     else if (y == cub->map_size_y - 1 && (!ft_isspace(cub->map_str[y][x]) || cub->map_str[y][x] !=  '1'))
    //         return (0);
    //     y ++;
    // }
    // return (1);
    
    char **m;
    m = cub->map_str;
    printf("\n");
    printf("MAP SIZE: X =%d Y =%d\n",cub->map_size_x, cub->map_size_y);
    while(y < cub->map_size_y)
    {
        while(x < cub->map_size_x)
        {
            if(is_notwall(m[y][x]))
            {
                if (is_empty(cub, x, y))
                {
                    printf("Map not closed x:%d y:%d\n",x,y);
                    return (0);
                }
            }
            x ++;
        }
        printf("\n");
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
    if(ft_isspace(m[y-1][x]) || ft_isspace(m[y+1][x]) || ft_isspace(m[y][x-1]) || ft_isspace(m[y][x+1]))
        return (1);
    return (0);
}

int is_notwall(int c)
{
    printf("%c",c);
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
        return (1);
    return (0);
}
