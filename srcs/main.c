/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/10 04:24:19 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void debug_printcub(t_cub *cub)
{
	if(cub->no_texpath)
		printf("NO: %s",cub->no_texpath);
	if(cub->so_texpath)
		printf("SO: %s",cub->so_texpath);
	if(cub->we_texpath)
		printf("WE: %s",cub->we_texpath);
	if(cub->ea_texpath)
		printf("EA: %s",cub->ea_texpath);
	printf("Window size X,Y {%d,%d}\n",cub->winsize_x,cub->winsize_x);
	printf("Errnum: %d\nDebug: %d\nMap_fd: %d\n",cub->errnum,cub->debug,cub->map_fd);
	printf("Map size: X,Y {%d,%d}\n",cub->map_size_x,cub->map_size_y);
	printf("Ceilling/Wall colors : #%06x,#%06x\n",cub->ce_color,cub->fl_color);
	printf("Map:\n");
}

int	parse_color(char *line)
{
	int color;
	int r;
	int g;
	int b;
	char **split;

	while(!ft_isdigit(*line))
		line ++;
	split = ft_split(line,',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	color = (r << 16) | (g << 8) | b;
	
	return (color);
}

void map_parse(char *line, t_cub *cub)
{
	(void)line;
	(void)cub;
}

void map_init(t_cub *cub)
{
	char *line;
	
	line = get_next_line(cub->map_fd);
	while(line)
	{
		if(ft_strnstr(line,"EA",2) && !cub->ea_texpath)
			cub->ea_texpath=ft_strdup(line);
		else if(ft_strnstr(line,"NO",2) && !cub->no_texpath)
			cub->no_texpath=ft_strdup(line);
		else if(ft_strnstr(line,"WE",2) && !cub->we_texpath)
			cub->we_texpath=ft_strdup(line);
		else if(ft_strnstr(line,"SO",2) && !cub->so_texpath)
			cub->so_texpath=ft_strdup(line);
		else if(ft_strnstr(line,"C ",2) && !cub->ce_color)
			cub->ce_color = parse_color(line);
		else if(ft_strnstr(line,"F ",2) && !cub->fl_color)
			cub->fl_color = parse_color(line);
		else
			map_parse(line,cub);
		free(line);
		line = get_next_line(cub->map_fd);
	}
	free(line);
}

t_cub *create_cub(char *path)
{
	t_cub *cub;

	(void)path;
	cub = (t_cub *)malloc(sizeof(t_cub));
	cub->map_fd = open(path,O_RDONLY);
	cub->errnum = 0;
	cub->debug = 0;
	map_init(cub);
	debug_printcub(cub);

	return (cub);
}

t_cub *init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_cub *cub;

	int test_fd;
	// if(argc != 2)
	// 	return (0);
	// if(!argv || !argv[1])
	// 	return (0);
	test_fd = open("./maps/01.cub",O_RDONLY);
	if(test_fd < 0)
		return (NULL);
	close(test_fd);
	cub = create_cub("./maps/01.cub");
	return (cub);
}

void error_exit(t_cub *c)
{
	if(c && c->errnum == 1)
	{
		printf("Cub3D ERROR : %d (cub3d -m for help)\n",c->errnum);
		exit (c->errnum);
	}
	else
	{
		printf("Cub3D INIT ERROR : APPRENDS A TAPER MERCI\n");
		exit (1);
	}
}

int main(int argc, char **argv)
{
	t_cub *cub;

	cub = init(argc, argv);
	if(!cub || cub->errnum)
		error_exit(cub);
	
}