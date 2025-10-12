/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/10/11 09:54:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
- mettre en place la FOV
- savoir l'orientation du perso (si y perso < a y mur = no texture ?)
- redimensionner les texture en fonction du perso
*/

/* si les optis de draw_walls.c suffisent pas il faudra regarder pour implementer les fixed points*/
/* virer les compteurs ca peut aider aussi lol ou alors les draw par dessus le buffer au lieu d'utiliser put string to img*/
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
		cub->player->input->y += 1;
	if(keycode == KEY_RIGHT)
		cub->player->input->y -= 1;
	if(keycode == KEY_STLEFT)
		cub->player->input->z += 1;
	if(keycode == KEY_STRIGHT)
		cub->player->input->z -= 1;
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

void draw_dirline(t_cub *cub, int x, int y, t_v2 *dir)
{
	int i;
	int x0;
	int y0;
		
	i = 0;
	while(i < 10)
	{
		x0 = x + i * dir->y;
		y0 = y + i * dir->x;	
		put_pixel(cub->buffer,x0,y0,0xFFFFFF);
		i ++;
	}
}

void move_nocol(t_cub *c, t_player *p)
{
	float posX;
	float posY;

	posX = p->pos->x;
	posX += p->dir->x * p->input->x * p->speed;
	posX += -p->dir->y * p->input->z * p->speed;
	if(posX < c->map_size_x && posX > 0)
		p->pos->x = posX;
	
	posY = p->pos->y;
	posY += p->dir->y * p->input->x * p->speed;
	posY += p->dir->x * p->input->z * p->speed;
	if(posY < c->map_size_y && posY > 0)
		p->pos->y = posY;
}

void move_player(t_cub *c)
{
	float oldDirX;
	float oldPlaneX;
	t_player *p;

	p = c->player;

	if(p->input->x != 0 || p->input->z != 0)
	{
			move_nocol(c,p);
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
	copy_buffer(cub->buffer, cub->background, cub);
	draw_walls(cub);
	mlx_put_image_to_window(cub->mlx,cub->window,cub->buffer->img,0,0);
	move_player(cub);
	cap_fps(cub);
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
	(void)cub;
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
	set_playerInitialRotation(cub);
	mlx_loop_hook(cub->mlx, render_loop, cub);
	mlx_loop(cub->mlx);
	free_all(cub);
	return (0);
}
