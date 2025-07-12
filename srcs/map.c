/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:26:27 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/12 00:41:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void map_init(t_cub *cub)
{
	char *line;
	
	line = get_next_line(cub->map_fd);
	while(line)
	{
		if (ft_strnstr(line,"EA",2) && !cub->ea_texpath)
			cub->ea_texpath = parse_texturepath(line);
		else if (ft_strnstr(line,"NO",2) && !cub->no_texpath)
			cub->no_texpath = parse_texturepath(line);
		else if (ft_strnstr(line,"WE",2) && !cub->we_texpath)
			cub->we_texpath = parse_texturepath(line);
		else if (ft_strnstr(line,"SO",2) && !cub->so_texpath)
			cub->so_texpath = parse_texturepath(line);
		else if (ft_strnstr(line,"C ",2) && !cub->ce_color)
			cub->ce_color = parse_color(line);
		else if (ft_strnstr(line,"F ",2) && !cub->fl_color)
			cub->fl_color = parse_color(line);
		else
			map_parse(line,cub);
		free(line);
		line = get_next_line(cub->map_fd);
	}
}

void map_parse(char *line, t_cub *cub)
{
	(void)cub;
	int i;
	char **map_str;

	i = 0;
	map_str = (char **)malloc (sizeof(char *) * MAP_SIZE);
	while (line)
	{
		if(ft_strlen(line) > 1)
		{
			map_str[i] = ft_strdup(line);
			i ++;
		}
		free(line);
		line = get_next_line(cub->map_fd);
	}
	cub->map_str = map_str;
	cub->map_size_y = i;
	cub->map_size_x = map_sizex(cub);
	map_parse2(cub);
}

void map_parse2(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	cub->map = (int **)malloc(sizeof(int *) * cub->map_size_y);
	while(i < cub->map_size_y)
	{
		cub->map[i] = malloc(sizeof(int) * cub->map_size_x);
		i ++;
	}
	init_map(cub);
	i = 0;
	while (i < cub->map_size_y)
	{
		while(j < cub->map_size_x)
		{
			add_to_map(i,j,cub);
			j ++;
		}
		j = 0;
		i ++;
	}
}

void add_to_map(int x, int y, t_cub* cub)
{
	char c;
	
	c = cub->map_str[x][y];
	if(y >= (int)ft_strlen(cub->map_str[x]) - 1)
		c = '0';
	if(c == '0' || c == ' ' || c == 0)
		cub->map[x][y] = EMPTY;
	else if(c == '1')
		cub->map[x][y] = WALL;
	else if(c == 'N')
		cub->map[x][y] = P_NORTH;
	else if(c == 'S')
		cub->map[x][y] = P_SOUTH;
	else if(c == 'E')
		cub->map[x][y] = P_EAST;
	else if(c == 'W')
		cub->map[x][y] = P_WEST;
	else
	{
		printf("x = %d, y = %d\n",x,y);
		cub->errnum = ERROR_MAP;
	}
}

int map_sizex(t_cub *cub)
{
	int i;
	int j;
	int size_x;

	i = 0;
	j = 0;
	size_x = 0;
	while(cub->map_str[i])
	{
		j = 0;
		while(cub->map_str[i][j])
			j ++;
		if (j > size_x)
			size_x = j;
		i ++;
	}
	return (size_x - 1);
}