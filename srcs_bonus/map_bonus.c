/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:26:27 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/27 16:52:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

void	map_parse(char *line, t_cub *cub)
{
	int		i;
	int		sizex;

	i = 0;
	sizex = 0;
	cub->map_str = (char **)malloc (sizeof(char *) * MAP_SIZE);
	while (is_line_empty(line))
	{
		free(line);
		line = get_next_line(cub->map_fd);
	}
	while (line)
	{
		cub->map_str[i] = ft_strdup(line);
		if ((int)ft_strlen(line) > sizex)
			sizex = ft_strlen(line);
		i ++;
		free(line);
		line = get_next_line(cub->map_fd);
	}
	cub->map_str[i] = NULL;
	cub->map_size_y = i;
	cub->map_size_x = sizex - 1;
	check_map(cub);
	map_parse2(cub);
}

void	map_parse2_init(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map = (int **)malloc(sizeof(int *) * cub->map_size_y);
	if (!cub->map)
	{
		cub->errnum = 2;
		return ;
	}
	while (i < cub->map_size_y)
	{
		cub->map[i] = malloc(sizeof(int) * cub->map_size_x);
		if (!cub->map[i])
		{
			cub->errnum = 2;
			return ;
		}
		i ++;
	}
	return ;
}

void	map_parse2(t_cub *cub)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	map_parse2_init(cub);
	init_map(cub);
	i = 0;
	while (i < cub->map_size_y)
	{
		j = 0;
		len = ft_strlen(cub->map_str[i]);
		while (j < cub->map_size_x)
		{
			if (j <= len)
				add_to_map(i, j, cub);
			else
				cub->map[i][j] = EMPTY;
			j ++;
		}
		free(cub->map_str[i]);
		i ++;
	}
}

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
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cub->player_pos[0] = x;
		cub->player_pos[1] = y;
	}
}
