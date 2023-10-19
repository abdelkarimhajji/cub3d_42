/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:13:53 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/19 11:41:55 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double to_rad(double degree)
{
    return (degree * (M_PI / 180));
}

void    direction_line(t_data *data)
{
    data->second_point_x = data->xp + cos(to_rad(data->corner)) * 100;
    data->second_point_y = data->yp + sin(to_rad(data->corner)) * 100;
}

void draw_line_dda(t_data *data, double x1, double y1, double x2, double y2, uint32_t color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    double xIncrement = (double)dx / steps;
    double yIncrement = (double)dy / steps;

    double x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
		mlx_put_pixel(data->img, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void    draw_rectangle(int x, int y, t_data *data, uint32_t color)
{
    int i;
    int j;
	
    i = x;
    j = y;
    while (y <  30 + j)
    {
        x = i;
        while (x <  30 + i)
        {
            mlx_put_pixel(data->img, x, y, color);
            x++;
        }
        y++;
    }
}


void draw_map(t_data *data)
{
	int i = 0;
    int j = 0;
	
	while (j < 11)
    {
        i = 0;
        while (i < 16)
        {
            if (myMap[j][i] == '1')
                draw_rectangle( i * 30, j * 30, data, 0xFFFFFFFF);
			if (myMap[j][i] == '0')
				draw_rectangle( i * 30, j * 30, data, 0x000000FF);
            if(myMap[j][i] == 'P')
            {
				draw_rectangle(data->xp = i * 30, data->yp = j * 30, data, 0x000000FF);
				mlx_put_pixel(data->img, i * 30, j * 30, 0xFF0000FF);
            }
            i++;
        }
        j++;
    }
}

void draw_map2(t_data *data)
{
	int i = 0;
    int j = 0;
	
	while (j < 11)
    {
        i = 0;
        while (i < 16)
        {
            if (myMap[j][i] == '1')
                draw_rectangle( i * 30, j * 30, data, 0xFFFFFFFF);
			if (myMap[j][i] == '0' || myMap[j][i] == 'P')
				draw_rectangle( i * 30, j * 30, data, 0x000000FF);
            i++;
        }
        j++;
    }
}

void draw_lines(t_data *data)
{
    int i;
    int j;
    i = data->corner + 1;
    j = data->corner - 1;
    while (i < 30 + data->corner)
    {
        draw_line_dda(data, data->xp, data->yp,data->xp + cos(to_rad(i)) * 100, data->yp + sin(to_rad(i)) * 100, 0xFF0000FF);
        draw_line_dda(data, data->xp, data->yp,data->xp + cos(to_rad(j)) * 100, data->yp + sin(to_rad(j)) * 100, 0xFF0000FF);
        j--;
        i++;
    }
}

int check_walls(t_data *data, int mode)
{
    int x;
    int y;
    
    x = data->xp;
    y = data->yp;
    
	if(mode == 'w')
	{
   
		x = x + cos(to_rad(data->corner)) * 2;
		y = y + sin(to_rad(data->corner)) * 2;
	}
    if(mode == 's')
	{
		x = x + cos(to_rad(data->corner)) * -2;
		y = y + sin(to_rad(data->corner)) * -2;
	}
    if(mode == 'd')
	{
        x = x - cos(to_rad(90) - to_rad(data->corner)) * 2;
		y = y + sin(to_rad(90) - to_rad(data->corner)) * 2;
	}
    if(mode == 'a')
	{
		x = x + cos(to_rad(90) - to_rad(data->corner)) * 2;
		y = y - sin(to_rad(90) - to_rad(data->corner)) * 2;
	}
    int i = x / 30;
    int j = y / 30;

    if(myMap[(int)(y / 30)][(int)(x / 30)] == '1')
        return 0;

    if(myMap[(int)(data->yp / 30)][(int)(x / 30)] == '1' && myMap[(int)(y+5 / 30)][(int)(data->xp / 30)] == '1')
    {
        printf("iam her int \n");
        return 0;
    }
    
    return 1;
}

static void ft_hook(void* param)
{
	t_data  *data = (t_data *)param;

	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if(data->corner >= 360)
			data->corner = 0;
		data->corner++;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		if(data->corner <= 0)
			data->corner = 360;
		data->corner--;
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_W) && check_walls(data, 'w'))
	{
		data->xp = data->xp + cos(to_rad(data->corner)) * 2;
		data->yp = data->yp + sin(to_rad(data->corner)) * 2;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_S) && check_walls(data, 's'))
	{
		data->xp = data->xp + cos(to_rad(data->corner)) * -2;
		data->yp = data->yp + sin(to_rad(data->corner)) * -2;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_D) && check_walls(data, 'd'))
	{
        data->xp = data->xp - cos(to_rad(90) - to_rad(data->corner)) * 2;
		data->yp = data->yp + sin(to_rad(90) - to_rad(data->corner)) * 2;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_A) && check_walls(data, 'a'))
	{
		data->xp = data->xp + cos(to_rad(90) - to_rad(data->corner)) * 2;
		data->yp = data->yp - sin(to_rad(90) - to_rad(data->corner)) * 2;
	}
	draw_map2(data);
	mlx_put_pixel(data->img, data->xp, data->yp , 0xFF0000FF);
	direction_line(data);
	draw_line_dda(data, data->xp, data->yp, data->second_point_x, data->second_point_y, 0xFF0000FF);
    draw_lines(data);
}

int main()
{
    t_data data;
    int i = 0;
    int j = 0;
    
	data.mlx = mlx_init(1556, 956, "42Balls", true);
	if (!data.mlx)
		return 1;
    data.img = mlx_new_image(data.mlx, 1556, 956);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		return 1;
	data.corner = 100;
	draw_map(&data);
	mlx_loop_hook(data.mlx, ft_hook, (void *)&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
    return 0;
}
