/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi/jelucian <vanfossi@student.42n    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:03:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/19 02:21:37 by vanfossi/je      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	param_check(t_cub *c)
{
	if (!c->no_texpath)
		return (0);
	if (!c->so_texpath)
		return (0);
	if (!c->we_texpath)
		return (0);
	if (!c->ea_texpath)
		return (0);
	if (!c->fl_color)
		return (0);
	if (!c->ce_color)
		return (0);
	else
		return (1);
}

int	char_check(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (i == 0 || i == (int)ft_strlen(str) - 2)
		{
			if (str[i] != '1' && str[i] != ' ')
				return (0);
		}
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i ++;
			if (str[i] != '1' && str[i] != '\n')
				return (0);
		}
		c = str[i];
		if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W'
			&& c != 'E' && c != ' ' && c != '\n')
			return (0);
		i ++;
	}
	return (1);
}

int	check_mapstr(t_cub *c)
{
	int	i;

	i = 0;
	if (!c->map_size_x)
		return (0);
	while (i < c->map_size_x)
	{
		if (!char_check (c->map_str[i]))
			return (0);
		i ++;
	}
	return (1);
}

int	file_check(t_cub *c)
{
	int	test_fd;

	test_fd = open(c->no_texpath, O_RDONLY);
	if (test_fd == -1)
		return (0);
	test_fd = open(c->so_texpath, O_RDONLY);
	if (test_fd == -1)
		return (0);
	test_fd = open(c->we_texpath, O_RDONLY);
	if (test_fd == -1)
		return (0);
	test_fd = open(c->ea_texpath, O_RDONLY);
	if (test_fd == -1)
		return (0);
	return (1);
}

void	check_map(t_cub *c)
{
	if (!param_check(c))
	{
		printf("Invalid parameters (textures or colors missing).\n");
		exit_maperror(c);
	}
	else if (!check_mapstr(c))
	{
		printf("Invalid map.\n");
		exit_maperror(c);
	}
	else if (!file_check(c))
	{
		printf("Invalid/missing texture file.\n");
		exit_maperror(c);
	}
	else if (!player_check(c))
	{
		printf("Invalid player position.\n");
		exit_maperror(c);
	}
	else
		return ;
}
