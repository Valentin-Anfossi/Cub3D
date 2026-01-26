/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:28:36 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/05 11:04:05 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

char	*parse_texturepath(char *line)
{
	char	**split;
	char	*re;

	split = ft_split(line, ' ');
	re = NULL;
	if (split[0])
		free(split[0]);
	if (split[1])
	{
		split[1][ft_strlen(split[1]) - 1] = '\0';
		re = ft_strdup(split[1]);
	}
	free(split[1]);
	free(split);
	return (re);
}

int	parse_color(char *line)
{
	int		color;
	int		r;
	int		g;
	int		b;
	char	**split;

	while (!ft_isdigit(*line))
		line ++;
	split = ft_split(line, ',');
	r = ft_atoi(split[0]);
	free(split[0]);
	g = ft_atoi(split[1]);
	free(split[1]);
	b = ft_atoi(split[2]);
	free(split[2]);
	color = (0xFF << 24) | (r << 16) | (g << 8) | b;
	free(split);
	return (color);
}
