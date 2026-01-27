/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:08:52 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/27 16:42:29 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
