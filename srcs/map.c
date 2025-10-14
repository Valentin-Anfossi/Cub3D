/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:26:27 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/12 16:22:16 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

//set CUB->ERRNUM IF MAP ERROR (NO RETURN or someshit)

void	map_init(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->map_fd);
	while (line)
	{
		if (ft_strnstr(line, "EA", 2) && !cub->ea_texpath)
			cub->ea_texpath = parse_texturepath(line);
		else if (ft_strnstr(line, "NO", 2) && !cub->no_texpath)
			cub->no_texpath = parse_texturepath(line);
		else if (ft_strnstr(line, "WE", 2) && !cub->we_texpath)
			cub->we_texpath = parse_texturepath(line);
		else if (ft_strnstr(line, "SO", 2) && !cub->so_texpath)
			cub->so_texpath = parse_texturepath(line);
		else if (ft_strnstr(line, "C ", 2) && !cub->ce_color)
			cub->ce_color = parse_color(line);
		else if (ft_strnstr(line, "F ", 2) && !cub->fl_color)
			cub->fl_color = parse_color(line);
		else if (line && ft_strlen(line) > 0 && line[0] != '\n')
		{
			map_parse(line, cub);
			break ;
		}
		free(line);
		line = get_next_line(cub->map_fd);
	}
}

void	map_parse(char *line, t_cub *cub)
{
	int		i;
	int		sizex;

	i = 0;
	sizex = 0;
	cub->map_str = (char **)malloc (sizeof(char *) * MAP_SIZE);
	while (line)
	{
		if (ft_strlen(line) > 1)
		{
			cub->map_str[i] = ft_strdup(line);
			if((int)ft_strlen(line) > sizex)
				sizex = ft_strlen(line);
			i ++;
		}
		free(line);
		line = get_next_line(cub->map_fd);
	}
	cub->map_str[i] = NULL;
	cub->map_size_y = sizex - 1;
	cub->map_size_x = i;
	map_parse2(cub);
}

void	map_parse2(t_cub *cub)
{
	int	i;
	int	j;
	int len;

	i = 0;
	j = 0;
	cub->map = (int **)malloc(sizeof(int *) * cub->map_size_x);
	while (i < cub->map_size_x)
	{
		cub->map[i] = malloc(sizeof(int) * cub->map_size_y);
		if (!cub->map[i])
			return;
		i ++;
	}
	init_map(cub);
	i = 0;
	while (i < cub->map_size_x)
	{
		j = 0;
		len = ft_strlen(cub->map_str[i]);
		while (j < cub->map_size_y)
		{
			if(j < len)
				add_to_map(i, j, cub);
			else
				cub->map[i][j] = EMPTY;
			j ++;
		}
		free(cub->map_str[i]);
		i ++;
	}
}

// int map_parse2_helper(t_cub *cub)
// {
// 	cub->map = (int **)malloc(sizeof(int *) * cub->map_size_x);
// 	while (i < cub->map_size_x)
// 	{
// 		cub->map[i] = malloc(sizeof(int) * cub->map_size_y);
// 		if (!cub->map[i])
// 			return (0);
// 		i ++;
// 	}	
// }

void	add_to_map(int x, int y, t_cub *cub)
{
	char	c;

	c = cub->map_str[x][y];
	if (c == '0' || c == ' ')
		cub->map[x][y] = EMPTY;
	else if (c == '1')
		cub->map[x][y] = WALL;
	else if (c == 'N')
		cub->map[x][y] = P_NORTH;
	else if (c == 'S')
		cub->map[x][y] = P_SOUTH;
	else if (c == 'E')
		cub->map[x][y] = P_EAST;
	else if (c == 'W')
		cub->map[x][y] = P_WEST;
	if (c == 'N' || c =='S' || c=='E' || c =='W')
	{
		cub->player_pos[0] = x;
		cub->player_pos[1] = y;
	}
}

int	map_sizex(t_cub *cub)
{
	int	i;
	int	j;
	int	size_x;

	i = 0;
	j = 0;
	size_x = 0;
	while (cub->map_str[i])
	{
		j = 0;
		while (cub->map_str[i][j])
			j ++;
		if (j > size_x)
			size_x = j;
		i ++;
	}
	return (size_x);
}
