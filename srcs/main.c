/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/20 14:28:16 by vanfossi         ###   ########.fr       */
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
	printf("KEY %d\n",keycode);
	if(keycode == KEY_UP)
		cub->player->input->x += 1;
	if(keycode == KEY_DOWN)
		cub->player->input->x -= 1;
	if(keycode == KEY_LEFT)
		cub->player->input->y += 1;
	if(keycode == KEY_RIGHT)
		cub->player->input->y -= 1;
	if(keycode == KEY_STLEFT)
		cub->player->input->z += 1;
	if(keycode == KEY_STRIGHT)
		cub->player->input->z -= 1;
	if(keycode == KEY_MOUSE)
	{
		if(cub->is_mouseActive)
			cub->is_mouseActive = 0;
		else
			cub->is_mouseActive = 1;
	}
	return (0);
}

int handle_keyRelease(int keycode, t_cub *cub)
{
	if(keycode == KEY_UP)
		cub->player->input->x -= 1;
	if(keycode == KEY_DOWN)
		cub->player->input->x += 1;
	if(keycode == KEY_LEFT)
		cub->player->input->y -= 1;
	if(keycode == KEY_RIGHT)
		cub->player->input->y += 1;
	if(keycode == KEY_STLEFT)
		cub->player->input->z -= 1;
	if(keycode == KEY_STRIGHT)
		cub->player->input->z += 1;
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
	cub->delta_time = frameTime * 1000;
	float fps = (1.0 / frameTime);
	char str[320];
	if(fps > 60)
		fps = 60;
	sprintf(str,"FPS :%.0f",fps); //ATTENTION C PAS AUTORISE (JE CROIS)
	mlx_string_put(cub->mlx,cub->window,0,cub->winsize_y,create_argb(1,255,255,255),str);
}

void draw_controls(t_cub *cub) 
{	
	char str[320];
	int x;
	int y;
	mlx_mouse_get_pos(cub->mlx, cub->window, &x,&y);
	sprintf(str,"Input :%d, %d Mouse : %d, %d",cub->player->input->x, cub->player->input->y,x,y); //ATTENTION C PAS AUTORISE (JE CROIS)
	mlx_string_put(cub->mlx,cub->window,0,cub->winsize_y-50,create_argb(1,255,255,255),str);
}

void move_player(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	int mouseX;
	int mouseY;
	t_player *p;

	p = c->player;
	if(p->input->x != 0)
	{
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
	if(c->is_mouseActive)
	{
		mlx_mouse_get_pos(c->mlx, c->window, &mouseX, &mouseY);
		p->input->y = -(mouseX - c->winsize_x/2);
		mlx_mouse_move(c->mlx,c->window,c->winsize_x/2,c->winsize_y/2);
	}
	if(p->input->z != 0)
	{
		p->pos->x += -p->dir->y * p->input->z * p->speed;
		p->pos->y += p->dir->x * p->input->z * p->speed;
	} 
}

t_v2 rotateVector(const t_v2 *vector, int deg)
{
	float f;
	t_v2 rotated;
	f = deg * M_PI / 180.0f;
	rotated.x = vector->x * cosf(f);
	rotated.y = vector->y * sinf(f);
	return (rotated);
}

void cap_fps(t_cub *cub)
{
	double sleep_time;
	
	if(cub->delta_time < 1000 / TARGET_FPS)
	{
		sleep_time = ((1000/TARGET_FPS) - cub->delta_time) * 1000;
		usleep(sleep_time);	
	}
}

int render_loop(t_cub *cub)
{
	if(!cub->mlx)
		return (0);
	
	// ft_memset(cub->buffer->data,0,cub->winsize_x * cub ->winsize_y * sizeof(int));
	copy_buffer(cub->buffer, cub->background, cub);
	draw_walls(cub);
	copy_buffer(cub->buffer_old, cub->buffer, cub);
	mlx_put_image_to_window(cub->mlx,cub->window,cub->buffer_old->img,0,0);

	move_player(cub);
	// draw_controls(cub);
	draw_fps(cub);
	cap_fps(cub);
	// cub->buffer_old = cub->buffer;
	return (1);
}

void set_playerInitialRotation(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	t_player *p;
	int	angle_degrees;
	float angle;

	p = c->player;
	angle_degrees = get_playerInitialDir(c);
	angle = angle_degrees *  M_PI / 180.0;
	oldDirX = p->dir->x;
	p->dir->x = p->dir->x * cos(angle) - p->dir->y * sin(angle);
	p->dir->y = oldDirX * sin(angle) + p->dir->y * cos(angle);
	oldPlaneX = p->plane->x;
	p->plane->x = p->plane->x * cos(angle) - p->plane->y * sin(angle);
	p->plane->y = oldPlaneX * sin(angle) + p->plane->y * cos(angle);
	
}

int handle_mouse(t_cub *cub)
{
	int x;
	int y;

	mlx_mouse_get_pos(cub->mlx,cub->window,&x,&y);
	// mlx_mouse_move()
	return (0);
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
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_mouse_hide(cub->mlx,cub->window);
	
	// mlx_mouse_hook(cub->window,handle_mouse,cub);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_no->img, 100, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_so->img, 200, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_we->img, 300, cub->winsize_y / 2.05);
	// mlx_put_image_to_window(cub->mlx, cub->window, cub->texture_ea->img, 400, cub->winsize_y / 2.05);
	set_playerInitialRotation(cub);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_loop(cub->mlx);

	free_all(cub);
}
