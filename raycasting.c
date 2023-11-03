/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:37:30 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 12:37:58 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ray_casting(t_cub3d *data, float dist, float ray_angle, int id_ray, int color)
{
    double height_wall;
    int xstart;
    int ystart;
    int xend;
    int yend;
    
	dist = dist * cos(to_rad(ray_angle) - to_rad(data->angle));
	height_wall = ((data->size_shape ) * height_win) / dist;
	xstart = id_ray;
	xend = id_ray;
	ystart = (height_win / 2) - (height_wall / 2);
	yend = (height_win / 2) + (height_wall / 2);

    if (ystart < 0)
        ystart = 0;
    if (yend > height_win)
        yend = height_win;
    while (ystart < yend)
    {
        if ( ystart >= 0 && ystart < height_win)
            mlx_put_pixel(data->img, (int)xstart, (int)ystart, color);
        ystart += 1;
    }
}
