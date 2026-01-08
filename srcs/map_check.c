/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:21:52 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/08 10:33:46 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_notexpath(t_cub *cub)
{
	char	*line;
	int		index;

	index = 0;
	line = get_next_line(cub->map_fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(cub->map_fd);
	}
	while (line[index] == ' ')
		index++;
	if (!line[index] || !line[index + 1] || line[index] != 'N'
		|| line[index + 1] != 'O')
	{
		free(line);
		return (0);
	}
	index += 2;
	while (line[index] == ' ')
		index++;
	cub->no_texpath = ft_substr(line, index, ft_strlen(line) - (index + 1));
	free(line);
	return (1);
}

int	get_sotexpath(t_cub *cub)
{
	char	*line;
	int		index;

	index = 0;
	line = get_next_line(cub->map_fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(cub->map_fd);
	}
	while (line[index] == ' ')
		index++;
	if (!line[index] || !line[index + 1]
		|| line[index] != 'S' || line[index + 1] != 'O')
	{
		free(line);
		return (0);
	}
	index += 2;
	while (line[index] == ' ')
		index++;
	cub->so_texpath = ft_substr(line, index, ft_strlen(line) - (index + 1));
	free(line);
	return (1);
}

int	get_wetexpath(t_cub *cub)
{
	char	*line;
	int		index;

	index = 0;
	line = get_next_line(cub->map_fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(cub->map_fd);
	}
	while (line[index] == ' ')
		index++;
	if (!line[index] || !line[index + 1]
		|| line[index] != 'W' || line[index + 1] != 'E')
	{
		free(line);
		return (0);
	}
	index += 2;
	while (line[index] == ' ')
		index++;
	cub->we_texpath = ft_substr(line, index, ft_strlen(line) - (index + 1));
	free(line);
	return (1);
}

int	get_eatexpath(t_cub *cub)
{
	char	*line;
	int		index;

	index = 0;
	line = get_next_line(cub->map_fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(cub->map_fd);
	}
	while (line[index] == ' ')
		index++;
	if (!line[index] || !line[index + 1]
		|| line[index] != 'E' || line[index + 1] != 'A')
	{
		free(line);
		return (0);
	}
	index += 2;
	while (line[index] == ' ')
		index++;
	cub->ea_texpath = ft_substr(line, index, ft_strlen(line) - (index + 1));
	free(line);
	return (1);
}
