/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:41:27 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 12:00:39 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_line_empty(char *line)
{
    if(!line)
        return (0);
    while(*line)
    {
        if(!ft_isspace(*line))
            return (0);
        line ++;       
    }
    return (1);
}

int get_floorclr(t_cub *cub)
{
    char *line;

    line = get_next_line(cub->map_fd);
    while(is_line_empty(line))
    {
        free(line);
        line = get_next_line(cub->map_fd);
    }
    if(!line)
        return (0);
    if(!line[0] || !line[1] || line[0] != 'F' || line[1] != ' ')
    {
        free(line);
        return (0);
    }
    cub->fl_color = parse_color2(line);
    free(line);
    if(cub->fl_color == -1)
        return (0);
    return (1);
}

int get_clclr(t_cub *cub)
{
    char *line;

    line = get_next_line(cub->map_fd);
    while(is_line_empty(line))
    {
        free(line);
        line = get_next_line(cub->map_fd);
    }
    if(!line)
        return (0);
    if(!line[0] || !line[1] || line[0] != 'C' || line[1] != ' ')
    {
        free(line);
        return (0);
    }
    cub->ce_color = parse_color2(line);
    free(line);
    if(cub->ce_color == -1)
        return (0);
    return (1);
}

int	parse_color2(char *line)
{
	int		color;
	char	**split;

    while (!ft_isdigit(*line) && *line && *line != '-')
    	line ++;
    split = ft_split(line, ',');
    color = 0;
    while(split[color])
    {
        if(is_line_empty(split[color]))
            break;
        color ++;
    }
    if(color != 3)
    {
        color = 0;
        while(split[color])
        {
            free(split[color]);
            color ++;
        }
        free(split);
        return (-1);
    }
    return(parsecolor2_helper(split, color));
}

int parsecolor2_helper(char **split, int color)
{
    int r;
    int g;
    int b;

    r = ft_atoi(split[0]);
    free(split[0]);
    g = ft_atoi(split[1]);
    free(split[1]);
    b = ft_atoi(split[2]);
    free(split[2]);
    if(color != 3)
    {
        return (-1);
    }
    color = (0xFF << 24) | (r << 16) | (g << 8) | b;
    free(split);
	if(r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
    {
        return(-1);
    }
    return (color);    
}
