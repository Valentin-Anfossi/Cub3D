/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:03:43 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 12:20:29 by vanfossi         ###   ########.fr       */
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
		c = str[i];
		if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W'
			&& c != 'E' && c != ' ' && c != '\n')
			{
				printf("Invalid char in map.\n");
				return (0);
			}
		i ++;
	}
	return (1);
}

int	check_mapstr(t_cub *c)
{
	int	i;

	i = 0;
	if (!c->map_size_y)
	{
		printf("Map missing ?\n");
		return (0);
	}
	while (i < c->map_size_y)
	{
		if (!char_check (c->map_str[i]))
			return (0);
		i ++;
	}
	return (1);
}

int	textfiles_check(t_cub *c)
{
	int	test_fd;
;
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
	if (!check_mapstr(c))
	{
		exit_maperror(c);
	}
	if(!check_foremptylines(c))
	{
		printf("Empty line in map.\n");
		exit_maperror(c);
	}
	if(!check_ismapclosed(c))
	{
		printf("Map isn't closed.\n");
		exit_maperror(c);
	}
	else if (!textfiles_check(c))
	{
		printf("Invalid/missing texture file.\n");
		exit_maperror(c);
	}
	else if(!check_player(c))
	{
		exit_maperror(c);
	}
	else
		return ;
}


