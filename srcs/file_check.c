/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 06:37:43 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/05 09:09:24 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Here we check for obvious file related errors like missing file, wrong extension etc...

#include "cub3d.h"

void file_error(int err)
{
    if(err == 1)
        printf("Invalid arguments (needs ./cub3d path/to/map.cub)\n");
    if(err == 2)
		printf("Invalid arguments (unexpected eof or no arguments)\n");
    if(err == 3)
        printf("Invalid mapfile (doesn't exist or cannot open)\n");
    if(err == 4)
        printf("Invalid file type (must end with .cub)\n");
    exit(1);
}

int ends_with_dotcub(char *str)
{
    int i;
    int j;
    char *ext;

    if(!str || ft_strlen(str) == 0)
        return (0);
    i = ft_strlen(str) - 1;
    j = 3;
    ext = ".cub";
    while(str[i] == ' ' || str[i] == '\n')
        i --;
    while(str[i] == ext[j])
    {
        i --;
        j --;
    }
    if(j <= 0)
        return(1);
    else
        return (0);
}

void file_check(int argc, char **argv)
{
    int temp_fd;
    
	if (argc != 2)
        file_error(1);
    if (!argv[1])
        file_error(2);
    if (!ends_with_dotcub(argv[1]))
        file_error(4);
    temp_fd = open(argv[1], O_RDONLY);
    if(temp_fd < 0)
        file_error(3);
    close(temp_fd);
}