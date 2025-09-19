/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/19 07:15:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- mettre en place la FOV
- savoir l'orientation du perso (si y perso < a y mur = no texture ?)
- redimensionner les texture en fonction du perso
*/
#include "cub3d.h"

int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		destroystuff(cub);

	if(keycode == KEY_UP)
		cub->player->input->x += 1;
	if(keycode == KEY_DOWN)
		cub->player->input->x -= 1;
	if(keycode == KEY_LEFT)
		cub->player->input->y -= 1;
	if(keycode == KEY_RIGHT)
		cub->player->input->y += 1;
	
	return (0);
}

int handle_keyRelease(int keycode, t_cub *cub)
{
	if(keycode == KEY_UP)
		cub->player->input->x -= 1;
	if(keycode == KEY_DOWN)
		cub->player->input->x += 1;
	if(keycode == KEY_LEFT)
		cub->player->input->y += 1;
	if(keycode == KEY_RIGHT)
		cub->player->input->y -= 1;
	return (0);
}

void copy_buffer(t_draw *dest, const t_draw *src, t_cub *cub)
{
	ft_memcpyfast(dest->data, src->data, (cub->winsize_x * cub->winsize_y) *sizeof(int));
}


void draw_fps(t_cub *cub) 
{
    double frameTime;

    cub->old_time = cub->time;
    gettimeofday(&(cub->time), NULL);
    frameTime = (cub->time.tv_sec - cub->old_time.tv_sec) +
                (cub->time.tv_usec - cub->old_time.tv_usec) * 1e-6;
    float fps = 1.0 / frameTime;
	char str[320];
	sprintf(str,"FPS :%f",fps); //ATTENTION C PAS AUTORISE (JE CROIS)
	mlx_string_put(cub->mlx,cub->window,0,cub->winsize_y,create_argb(1,255,255,255),str);
}

void draw_controls(t_cub *cub) 
{	
	char str[320];
	sprintf(str,"Input :%d, %d",cub->player->input->x, cub->player->input->y); //ATTENTION C PAS AUTORISE (JE CROIS)
	mlx_string_put(cub->mlx,cub->window,0,cub->winsize_y-50,create_argb(1,255,255,255),str);
}

void move_player(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	t_player *p;

	p = c->player;
	if(p->input->x != 0)
	{
		// if(c->map[(int)(p->pos->x + p->input->x)][(int)p->pos->y] == EMPTY)
		// {
		// }
			p->pos->x += p->dir->x * p->input->x * p->speed;
			p->pos->y += p->dir->y * p->input->x * p->speed;
	}
	if(p->input->y != 0)
	{
		oldDirX = p->dir->x;
		p->dir->x = p->dir->x * cos(p->rot_speed * p->input->y) - p->dir->y * sin(p->rot_speed * p->input->y);
		p->dir->y = oldDirX * sin(p->rot_speed * p->input->y) + p->dir->y * cos(p->rot_speed * p->input->y);
		oldPlaneX = p->plane->x;
		p->plane->x = p->plane->x * cos(p->rot_speed * p->input->y) - p->plane->y * sin(p->rot_speed * p->input->y);
		p->plane->y = oldPlaneX * sin(p->rot_speed * p->input->y) + p->plane->y * cos(p->rot_speed * p->input->y);
	}
}

int render_loop(t_cub *cub)
{
	if(!cub->mlx)
		return (0);
	
	ft_memset(cub->buffer->data,0,cub->winsize_x * cub ->winsize_y * sizeof(int));
	copy_buffer(cub->buffer, cub->background, cub);
	move_player(cub);
	draw_walls(cub);
	mlx_put_image_to_window(cub->mlx,cub->window,cub->buffer->img,0,0);
	draw_fps(cub);
	draw_controls(cub);
	// cub->buffer_old = cub->buffer;
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init(argc, argv);
	if (!cub || cub->errnum != 0)
		error_exit(cub);
	mlx_hook(cub->window, 17, 1L << 17, destroystuff, cub);
	mlx_hook(cub->window, KeyPress, KeyPressMask, handle_key, cub);
	mlx_hook(cub->window, KeyRelease, KeyRelease, handle_keyRelease, cub);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_no->img, 100, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_so->img, 200, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_we->img, 300, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_ea->img, 400, cub->winsize_y / 2.05);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_loop(cub->mlx);

	free_all(cub);
}
