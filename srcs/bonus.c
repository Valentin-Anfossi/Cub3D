/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:19:47 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/07 15:42:50 by vanfossi         ###   ########.fr       */
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

void draw_hline(t_cub *cub, int x1, int x2, int y, int color)
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
        draw_hline(cub,x0 - x,x0 + x, y0 + y, create_argb(1,255,255,255));
        draw_hline(cub,x0 - x,x0 + x, y0 - y, create_argb(1,255,255,255));
        draw_hline(cub,x0 - y,x0 + y, y0 + x, create_argb(1,255,255,255));
        draw_hline(cub,x0 - y,x0 + y, y0 - x, create_argb(1,255,255,255));
        
        y += 1;
        err += 1 + 2*y;
        if(2*(err - x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2 * x;
        }
    }
}

void draw_square(t_cub *cub, int x0, int y0, int size,int color)
{
    int y;

    y = y0;
    while(y < (y0 + size))
    {
        draw_hline(cub,x0,x0+size,y,color);
        y ++;
    }
}

void draw_minimap(t_cub *cub)
{
    t_minimap *mi;

    mi = cub->minimap;
    mi->xpos = cub->player->pos->x;
    mi->ypos = cub->player->pos->y;
    if(cub->map_fullscreen)
    {
        mi->zoom = .05;
        mi->map_sizey = cub->winsize_y;
        mi->map_sizex = cub->winsize_x;
    }
    else
    {
        mi->zoom = .035;
        mi->map_sizey = cub->winsize_y / 3;
        mi->map_sizex = cub->winsize_y / 3;
        draw_square(cub, 0, 0, mi->map_sizey,create_argb(0,255,0,0));
        draw_square(cub, 3, 3, mi->map_sizey-6,create_argb(0,0,0,0));
    }
    draw_minimap_helper(cub,mi);
}

void draw_minimap_helper(t_cub *cub, t_minimap *mi)
{
    int wall;

    mi->y = 0;
    mi->x = 0;
    while(mi->y <= mi->map_sizex)
    {
        mi->x = 0;
        while(mi->x <= mi->map_sizey)
        {
            mi->xmap = mi->xpos + (mi->x - ((mi->map_sizey) / 2)) * mi->zoom;
            mi->ymap = mi->ypos + (mi->y - ((mi->map_sizex) / 2)) * mi->zoom;
            if(mi->xmap < cub->map_size_y && mi->xmap >= 0 && mi->ymap < cub->map_size_x && mi->ymap >= 0)
            {
                wall = cub->map[(int)mi->xmap][(int)mi->ymap];
                if(wall == 1)
                    put_pixel(cub->buffer,mi->y,mi->x,create_argb(1,0,255,0)); 
            }
            mi->x ++;
        }
        mi->y ++;
    }

    draw_minimap_player(cub,mi);
}

void	draw_line(t_v2 p1, t_v2 p2, t_cub *cub, int norminette)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	float	step;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = p1.x;
	y = p1.y;
	while (norminette <= step)
	{
        put_pixel(cub->buffer,x,y,create_argb(1,255,64,64));
		x = x + dx;
		y = y + dy;
		norminette ++;
	}
}

void draw_minimap_player(t_cub *cub, t_minimap *mi)
{
    t_v2 p0;
    t_v2 p1;

    p0.x = (mi->map_sizex/2) ;
    p0.y = (mi->map_sizey/2) ;
    if(cub->map_fullscreen)
    {
        p1.x = p0.x + (7.5 *(cub->player->dir->y));
        p1.y = p0.y + (7.5 *(cub->player->dir->x));
        draw_circle(cub, (mi->map_sizex)/2, (mi->map_sizey)/2, 5);
        draw_thickline(p0,p1,cub);
    }
    else
    {
        p1.x = p0.x + (12.5 *(cub->player->dir->y));
        p1.y = p0.y + (12.5 *(cub->player->dir->x));
        draw_circle(cub, (mi->map_sizex)/2, (mi->map_sizey)/2, 10);
        draw_thickline(p0,p1,cub);
    }    
}

void draw_thickline(t_v2 p0, t_v2 p1, t_cub *cub)
{
    draw_line(p0,p1,cub,0);
    p0.y += 1;
    p1.y += 1;
    draw_line(p0,p1,cub,0);
    p0.x += 1;
    p1.x += 1;
    draw_line(p0,p1,cub,0);
    p0.y -= 2;
    p1.y -= 2;
    draw_line(p0,p1,cub,0);
    p0.x -= 2;
    p1.x -= 2;
    draw_line(p0,p1,cub,0);
}

t_minimap *malloc_minimap()
{
    t_minimap *minimap;

    minimap = malloc(sizeof(t_minimap));
    minimap->map_sizex = 0;
    minimap->map_sizey = 0;
    minimap->x = 0;
    minimap->y = 0;
    minimap->xpos = 0;
    minimap->ypos = 0;
    minimap->xmap = 0;
    minimap->ymap = 0;
    minimap->zoom = 0;
    
    return (minimap);
}

// void draw_minimap(t_cub *cub)
// {
//     // draw_square(cub, 0, 0, cub->winsize_y/4,create_argb(0,255,0,0));
//     // draw_square(cub, 3, 3, (cub->winsize_y/4)-6,create_argb(0,0,0,0));
//     int map_size = cub->winsize_x;
//     draw_circle(cub, (map_size)/2, (map_size) /2, 5);

//     float xpos = cub->player->pos->x;
//     float ypos = cub->player->pos->y;
//     int x = 0;
//     int y = 0;
//     float xmap = 0;
//     float ymap = 0;
    
//     // 50 50
//     while(x <= map_size)
//     {
        
//         y = 0;
//         while(y <= map_size)
//         {
//             // xmap = xpos + (y - (map_size) / 2) * 0.01;
//             // ymap = ypos + (x - (map_size) / 2) * 0.01;
//             if(xmap >= cub->map_size_y|| xmap < 0 || ymap >= cub->map_size_x|| ymap < 0)
//             {
//             }
//             else
//             {
//                 int wall = cub->map[(int)xmap][(int)ymap];
//                 if(wall == 1)
//                     put_pixel(cub->buffer,x,y,create_argb(1,0,255,0));
//             }
//             y ++;
//         }
//         x ++;
//     }
// }

