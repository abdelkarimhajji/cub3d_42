/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:13:53 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/28 21:51:05 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double to_rad(double degree)
{
    return (degree * (M_PI / 180));
}


void    direction_line(t_data *data)
{
    int ax;
    int ay;
    data->second_point_x = data->xp + cos(to_rad(data->corner)) * 500;
    data->second_point_y = data->yp + sin(to_rad(data->corner)) * 500;
}

int create_trgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void draw_ceil(t_data *data)
{
    int i ;
    int j = 0;
    while (j < 956)
    {
        i = 0;
        while (i < 1000)
        {
            if(j < 956 / 2)
                mlx_put_pixel(data->img, i, j, 0x0000FFFF);
            else
                mlx_put_pixel(data->img, i, j, 0x00FF00FF);
            i++;
        }
        j++;
    }
    
}

void draw_floor(t_data *data)
{
    
}


void draw_line_dda(t_data *data, double x1, double y1, double x2, double y2, uint32_t color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    double xIncrement = (double)dx / steps;
    double yIncrement = (double)dy / steps;

    double x = x1, y = y1;
    double t1 , t2;
    for (int i = 0; i <= steps; i++)
    {
        if (myMap[(int)(floor(y) / 30)][(int)(floor(x) / 30)] == '1' ||
            (myMap[(int)(floor(y) / 30)][(int)(floor(x + xIncrement) / 30)] == '1' 
            &&  myMap[(int)(floor(y + yIncrement) / 30)][(int)(floor(x) / 30)] == '1'))
            break;
		mlx_put_pixel(data->img, floor(x), floor(y), color);
        x += xIncrement;
        y += yIncrement;
        data->xray = x;
        data->yray = y;
    }
    if(data->ray_angle >= 0 && data->ray_angle <= 90)
        data->dist = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
    else if(data->ray_angle >= 90 && data->ray_angle <= 180)
        data->dist = sqrt(pow(x1 - x, 2) + pow(y - y1, 2));
    else if(data->ray_angle >= 180 && data->ray_angle <= 270)
        data->dist = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
    else if(data->ray_angle >= 270 && data->ray_angle <=  360)
        data->dist = sqrt(pow(x - x1, 2) + pow(y1 - y, 2));
}

void draw_line_dda2(t_data *data, double x1, double y1, double x2, double y2, uint32_t color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    double xIncrement = (double)dx / steps;
    double yIncrement = (double)dy / steps;

    double x = x1, y = y1;
    double t1 , t2;
    for (int i = 0; i <= steps; i++)
    {
		mlx_put_pixel(data->img, floor(x), floor(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void	raycast(t_data *data)
{
	// t_coord	start;
	// t_coord	end;
    double height_wall;
	int		proj_plane;
    float xstart;
    float ystart;
    float xend;
    float yend;
    
	// proj_plane = (1000 / 2) / tan(60 / 2);
	data->dist = data->dist * cos(to_rad(data->ray_angle) - to_rad(data->corner));
	height_wall = (60 * 956) / data->dist;
	xstart = data->n_rays;
	xend = data->n_rays;
	ystart = (956 / 2) - (height_wall / 2);
	yend = (956 / 2) + (height_wall / 2);
    // draw_line_dda2(data, x1, y1, x2, y2, 0xFF0000FF)
    // draw_line_dda2(data, xstart, xend,ystart, yend, 0xFF0000FF);
    while (ystart < yend)
    {
        // printf("x:%f y:%f\n", xstart, ystart);
        if (xstart >= 0 && xstart <= 1000 && ystart >= 0 && ystart <= 956)
            // mlx_put_pixel(data->img, (int)xstart, (int)ystart, 0xFF0000FF);
        ystart += 1.0f;
    }

	// draw_texture(start, game, ray);
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
				draw_rectangle(data->xp = i * 30 + 15, data->yp = j * 30 + 15, data, 0x000000FF);
				mlx_put_pixel(data->img, i * 30, j * 30, 0xFF0000FF);
            }
            i++;
        }
        j++;
    }
    data->lengx = i;
    data->lengy = j;
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
    float i;
    float j;
    float count = 0;

    double encriment; 
    encriment = 60.0 / 1000.0;

    
    i = data->corner - 30;
    data->n_rays = 0;
    while (count < 1000)
    {
        if((int)i > 360)
            i -= 360;
        else if ((int)i < 0)
            i += 360;
        draw_line_dda(data, data->xp, data->yp,data->xp + cos(to_rad(i)) * 500, data->yp + sin(to_rad(i)) * 500, 0xFF0000FF);
        count += 1;
        data->ray_angle = i;
        i +=  encriment;
        raycast(data);
        data->n_rays++;
        // printf("dist id[%f] => %d\n",count, (int)data->dist);
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
		x = x + cos(to_rad(data->corner)) * 3;
		y = y + sin(to_rad(data->corner)) * 3;
	}
    if(mode == 's')
	{
		x = x + cos(to_rad(data->corner)) * -3;
		y = y + sin(to_rad(data->corner)) * -3;
	}
    if(mode == 'd')
	{
        x = x - cos(to_rad(90) - to_rad(data->corner)) * 3;
		y = y + sin(to_rad(90) - to_rad(data->corner)) * 3;
	}
    if(mode == 'a')
	{
		x = x + cos(to_rad(90) - to_rad(data->corner)) * 3;
		y = y - sin(to_rad(90) - to_rad(data->corner)) * 3;
	}
    int i = x / 30;
    int j = y / 30;

    if(myMap[(int)(y / 30)][(int)(x / 30)] == '1' 
        || (myMap[(int)(data->yp / 30)][(int)(x/ 30)] == '1' 
        && myMap[(int)(y / 30)][(int)(data->xp / 30)] == '1'))
    {
        // printf("iam her int \n");
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
		data->xp = data->xp + cos(to_rad(data->corner)) * 3;
		data->yp = data->yp + sin(to_rad(data->corner)) * 3;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_S) && check_walls(data, 's'))
	{
		data->xp = data->xp + cos(to_rad(data->corner)) * -3;
		data->yp = data->yp + sin(to_rad(data->corner)) * -3;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_D) && check_walls(data, 'd'))
	{
        data->xp = data->xp - cos(to_rad(90) - to_rad(data->corner)) * 3;
		data->yp = data->yp + sin(to_rad(90) - to_rad(data->corner)) * 3;
	}
    if(mlx_is_key_down(data->mlx, MLX_KEY_A) && check_walls(data, 'a'))
	{
		data->xp = data->xp + cos(to_rad(90) - to_rad(data->corner)) * 3;
		data->yp = data->yp - sin(to_rad(90) - to_rad(data->corner)) * 3;
	}
    draw_ceil(data);
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
    
    data.width = 1000;
	data.mlx = mlx_init(data.width, 956, "42Balls", true);
	if (!data.mlx)
		return 1;
    data.img = mlx_new_image(data.mlx, 1000, 956);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		return 1;
	data.corner = 90;
	draw_map(&data);
	mlx_loop_hook(data.mlx, ft_hook, (void *)&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
    return 0;
}
