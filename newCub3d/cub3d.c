/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/25 10:45:36 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


float   to_rad(float degree)
{
    return(degree * (M_PI / 180));
}

void    draw_line_dda(t_cub3d *data, float  x1, float   y1, float  x2, float  y2, uint32_t color)
{
    float   dx;
    float   dy;
    float   steps;
    float   increamentx;
    float   increamenty;
    int i = 0;
    
    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    increamentx = dx /steps;
    increamenty = dy / steps;
    while (i <= steps)
    {
        mlx_put_pixel(data->img, round(x1), round(y1), 0xFF0000FF);
        x1 += increamentx;
        y1 += increamenty;        
        i++;
    }
}

void    init_data(t_cub3d *data)
{
    data->width_map = 15;
    data->height_map = 11;
    data->angle = 50;
}

void    draw_rectangle(int x, int y, t_cub3d *data, uint32_t color)
{
    int i;
    int j;
	
    i = x;
    j = y;
    while (y <  size_shape + j)
    {
        x = i;
        while (x <  size_shape + i)
        {
            mlx_put_pixel(data->img, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_map(t_cub3d *data, int mode)
{
	int i = 0;
    int j = 0;
	
	while (j < 11)
    {
        i = 0;
        while (i < 16)
        {
            if (myMap[j][i] == '1')
                draw_rectangle( i * size_shape, j * size_shape, data, 0xFFFFFFFF);
			if (myMap[j][i] == '0' || (mode == 0 && myMap[j][i] == 'P'))
				draw_rectangle( i * size_shape, j * size_shape, data, 0x000000FF);
            if(myMap[j][i] == 'P' && mode)
            {
				draw_rectangle(i * size_shape, j * size_shape, data, 0x000000FF);
				mlx_put_pixel(data->img, data->px = (i * size_shape) + 13, data->py = (j * size_shape) + 13, 0xFF0000FF);
            }
            i++;
        }
        j++;
    }
}

int    check_wall(t_cub3d *data)
{
    int x;
    int y;
    
    if(mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        x = data->px + (cos(to_rad(data->angle)) * move_step);
        y = data->py + (sin(to_rad(data->angle)) * move_step);
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        x = data->px - (cos(to_rad(data->angle)) * move_step);
        y = data->py - (sin(to_rad(data->angle)) * move_step);
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        x = data->px - cos(to_rad(90) - to_rad(data->angle)) * move_step;
	    y = data->py + sin(to_rad(90) - to_rad(data->angle)) * move_step;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        x = data->px + cos(to_rad(90) - to_rad(data->angle)) * move_step;
	    y = data->py - sin(to_rad(90) - to_rad(data->angle)) * move_step;
    }
    if(myMap[(int)(y / size_shape)][(int)(x / size_shape)] == '1' || (myMap[(int)(y / size_shape)][(int)(data->px / size_shape)] == '1' && myMap[(int)(data->py / size_shape)][(int)(x / size_shape)] == '1'))
        return 0;
    return 1;
}

void    draw(void   *param)
{
    t_cub3d *data = (t_cub3d *)param;

    if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT) )
    {
        data->angle += speed_rotate;
        if(data->angle >= 360)
            data->angle = 0;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)  )
    {
        data->angle -= speed_rotate;
        if (data->angle <= 0)
            data->angle = 360;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_W) && check_wall(data))
    {
        data->px = data->px + (cos(to_rad(data->angle)) * move_step);
        data->py = data->py + (sin(to_rad(data->angle)) * move_step);
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_S) && check_wall(data))
    {
        data->px = data->px - (cos(to_rad(data->angle)) * move_step);
        data->py = data->py - (sin(to_rad(data->angle)) * move_step);
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_D) && check_wall(data))
    {
        data->px = data->px - cos(to_rad(90) - to_rad(data->angle)) * move_step;
	    data->py = data->py + sin(to_rad(90) - to_rad(data->angle)) * move_step;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_A) && check_wall(data))
    {
        data->px = data->px + cos(to_rad(90) - to_rad(data->angle)) * move_step;
	    data->py = data->py - sin(to_rad(90) - to_rad(data->angle)) * move_step;
    }
    // printf("%f\n", data->angle);
    draw_map(data, 0);
    mlx_put_pixel(data->img, data->px, data->py, 0xFF0000FF);

    draw_line_dda(data, data->px, data->py, data->px + (cos(to_rad(data->angle)) * 100),
     data->py + (sin(to_rad(data->angle)) * 100), 0xFF0000FF);
}

int main(int ac, char **av)
{
    t_cub3d     data;
    
    data.mlx = mlx_init(width_win, height_win, "cub3d", true);
    if(!data.mlx)
        return (1);
    data.img = mlx_new_image(data.mlx, width_win, height_win);
    if(!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0)) < 0 )
        return(1);
    init_data(&data);
    draw_map(&data, 1);
    mlx_loop_hook(data.mlx, draw, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (0);
}