/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:03:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/16 23:55:28 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// NO SO WE EA F C

void param_check(char *str, int *check)
{
    if(ft_strncmp(str,"NO ",3))
        check[0] = 1;
    if(ft_strncmp(str,"SO ", 3))
        check[1] = 1;    
    if(ft_strncmp(str,"WE ", 3))
        check[2] = 1;
    if(ft_strncmp(str,"EA ", 3))
        check[3] = 1;  
    if(ft_strncmp(str,"F ", 2))
        check[4] = 1;  
    if(ft_strncmp(str,"C ", 2))
        check[5] = 1;
    else
        return;
}

int all_params(int *check)
{
    int i;

    i = 0;
    while(i < 6)
    {
        if (check[i] == 0)
        {
            return (0);
        }
        i ++;
    }
    return (1);
}



void check_map(t_cub *c)
{
    int i;
    int *check;

    i = 0;
    check = malloc(sizeof(int) * 6);
    while(i < 6)
    {
        check[i] = 0;
        i ++;
    }
    i = 0;
    (void)c;
    while(c->map_str[i])
    {
        printf("hop %s\n",c->map_str[i]);
        param_check(c->map_str[i],check);
        i ++;
    }
    if(all_params(check) == 1)
        printf("CHecks ok !\n");
    // free(check);
}
