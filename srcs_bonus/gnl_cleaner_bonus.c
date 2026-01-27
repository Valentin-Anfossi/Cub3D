/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_cleaner_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:08:52 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/27 16:55:02 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	gnl_cleaner(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
