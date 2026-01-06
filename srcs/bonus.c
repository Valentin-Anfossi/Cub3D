/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:19:47 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/06 17:04:19 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int is_colliding(t_cub *c, float x, float y)
{
    
	int		check[4];
	check[0] = (int)(x - COL_DIST);
	check[1] = (int)(x + COL_DIST);
	check[2] = (int)(y - COL_DIST);
	check[3] = (int)(y + COL_DIST);

	return (
	c->map[check[0]][(int)y] == 1 ||
	c->map[check[1]][(int)y] == 1 ||
	c->map[(int)x][check[2]] == 1 ||
	c->map[(int)x][check[3]] == 1);
}

void move_col(t_cub *c, t_player *p)
{
	float 	new_x;
	float 	new_y;
	float	test_x;
	float	test_y;

	new_x = p->pos->x + (p->dir->x * p->input->x * p->speed) + (-p->dir->y * p->input->z * p->speed);
	new_y = p->pos->y + (p->dir->y * p->input->x * p->speed) + (p->dir->x * p->input->z * p->speed);
	test_x = new_x;
	test_y = p->pos->y;
	if(!is_colliding(c, test_x, test_y))
    {
		p->pos->x = test_x;
    }
	test_y = new_y;
	test_x = p->pos->x;
	if(!is_colliding(c,test_x,test_y))
    {
		p->pos->y = test_y;
    }
}

void mouse_rotate(t_cub *cub)
{
    int x;
	int y;

    mlx_mouse_get_pos(cub->mlx,cub->window,&x,&y);
    cub->player->input->y = (int)((-(x - (cub->winsize_x/2))) * MOUSE_SENS);   
	mlx_mouse_move(cub->mlx,cub->window,cub->winsize_x/2,cub->winsize_y/2);
}

void draw_line(t_cub *cub, int x1, int x2, int y, int color)
{
    while(x1 <= x2)
    {
        put_pixel(cub->buffer,x1,y,color);
        x1++;
    }
}

void draw_circle(t_cub *cub,int x0, int y0, int radius)
{
    int x;
    int y;
    int err;

    x = radius;
    y = 0;
    err = 0;

    while(x >= y)
    {
        draw_line(cub,x0 - x,x0 + x, y0 + y, create_argb(1,0,255,0));
        draw_line(cub,x0 - x,x0 + x, y0 - y, create_argb(1,0,255,0));
        draw_line(cub,x0 - y,x0 + y, y0 + x, create_argb(1,0,255,0));
        draw_line(cub,x0 - y,x0 + y, y0 - x, create_argb(1,0,255,0));
        
        y += 1;
        err += 1 + 2*y;
        if(2*(err - x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

void draw_minimap(t_cub *cub)
{
    draw_circle(cub, 25, 25, 10);
    // put_pixel(cub->buffer,(cub->winsize_y/3)/2,(cub->winsize_y/3)/2,create_argb(1,255,0,0));
    // draw_line(cub,0,50,10,create_argb(1,0,255,0));
}