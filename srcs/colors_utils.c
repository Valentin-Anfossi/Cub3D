/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 03:14:47 by vanfossi          #+#    #+#             */
/*   Updated: 2025/09/16 03:37:35 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_mult(int color, float ratio)
{
	int r;
	int g;
	int b;
	int ret;
	
	r = (color >> 16) & 0xFF;
    g = (color >> 8)  & 0xFF;
    b = color & 0xFF;
	r = (int)(r * ratio);
	g = (int)(g * ratio);
	b = (int)(b * ratio);
	ret = (r << 16) | (g << 8) | b;	
	return (ret);	
}

float remap(float ratio,float low, float high)
{
	return(((high - low) * ratio) + low);
}