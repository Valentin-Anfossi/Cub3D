/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:26:27 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/05 15:44:42 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

//en cours : il faut check si les parametres de textures sont dans lordre dans le file
//on fait deja la verif si la texture est bonne plus loin donc pas besoin

// void	map_init(t_cub *cub)
// {
// 	char	*line;

// 	line = get_next_line(cub->map_fd);
// 	while (line)
// 	{
// 		if (ft_strnstr(line, "EA", 2) && !cub->ea_texpath)
// 			cub->ea_texpath = parse_texturepath(line);
// 		else if (ft_strnstr(line, "NO", 2) && !cub->no_texpath)
// 			cub->no_texpath = parse_texturepath(line);
// 		else if (ft_strnstr(line, "WE", 2) && !cub->we_texpath)
// 			cub->we_texpath = parse_texturepath(line);
// 		else if (ft_strnstr(line, "SO", 2) && !cub->so_texpath)
// 			cub->so_texpath = parse_texturepath(line);
// 		else if (ft_strnstr(line, "C ", 2) && !cub->ce_color)
// 			cub->ce_color = parse_color(line);
// 		else if (ft_strnstr(line, "F ", 2) && !cub->fl_color)
// 			cub->fl_color = parse_color(line);
// 		else if (line && ft_strlen(line) > 0 && line[0] != '\n')
// 		{
// 			map_parse(line, cub);
// 			break ;
// 		}
// 		free(line);
// 		line = get_next_line(cub->map_fd);
// 	}
// }

void map_init(t_cub *cub)
{
	if(!get_notexpath(cub))
	{
		printf("Error with texture North (invalid, absent or wrong order)\n");
		exit_maperror(cub);	
	}
	if(!get_sotexpath(cub))
	{
		printf("Error with texture South (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if(!get_wetexpath(cub))
	{
		printf("Error with texture West (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if(!get_eatexpath(cub))
	{
		printf("Error with texture East (invalid, absent or wrong order)\n");
		exit_maperror(cub);
	}
	map_init_helper(cub);
}

void map_init_helper(t_cub *cub)
{
	if(!get_floorclr(cub))
	{
		printf("Error with floor color (invalid RGB, absent or wrong order)\n");
		exit_maperror(cub);
	}
	if(!get_clclr(cub))
	{
		printf("Error with ceiling color (invalid RGB, absent or wrong order)\n");
		exit_maperror(cub);
	}
	map_parse(get_next_line(cub->map_fd),cub);
}

//Skip empty lines
//check if line start with NO (if it doesn't = error)
//add NO to no_texpath
//etc.. with WE EA SO C F
//for colors, check if rgb format is correct

void	map_parse(char *line, t_cub *cub)
{
	int		i;
	int		sizex;

	i = 0;
	sizex = 0;
	cub->map_str = (char **)malloc (sizeof(char *) * MAP_SIZE);
	while(is_line_empty(line))
		line = get_next_line(cub->map_fd);
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
	cub->map_size_y = i; //mapsizex 1 PB
	cub->map_size_x = sizex - 1;
	check_map(cub);
	map_parse2(cub);
}

void	map_parse2_init(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map = (int **)malloc(sizeof(int *) * cub->map_size_x);
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
		if (cub->player_pos[0] != 0 && cub->player_pos != 0)
		{
			printf("Error : Player position declared twice\n");
			
		}
		cub->player_pos[0] = x;
		cub->player_pos[1] = y;
	}
}

