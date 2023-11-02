/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/02 20:19:59 by ahajji           ###   ########.fr       */
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
        mlx_put_pixel(data->img_map, round(x1), round(y1), color);
        x1 += increamentx;
        y1 += increamenty;        
        i++;
    }
}

void    init_data(t_cub3d *data)
{
    data->width_map = 30;
    data->height_map = 12;
    data->angle = 270;
    data->number_rays = width_win;
    if(width_win / 9 > height_win / 9)
        data->size_map = width_win / 9;
    else
        data->size_map = height_win / 9;
    if(data->height_map > data->width_map)
        data->size_shape = data->size_map / data->height_map; 
    else
        data->size_shape = data->size_map / data->width_map; 
    data->old_x = width_win;
}

void    draw_rectangle(int x, int y, t_cub3d *data, uint32_t color)
{
    int i;
    int j;
	
    i = x;
    j = y;
    while (y <  data->size_shape + j)
    {
        x = i;
        while (x <  data->size_shape + i)
        {
            mlx_put_pixel(data->img_map, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_map(t_cub3d *data, int mode)
{
	int i = 0;
    int j = 0;
	
	while (j < data->height_map)
    {
        i = 0;
        while (i < data->width_map)
        {
            if (myMap[j][i] == '1')
                draw_rectangle( i * data->size_shape, j * data->size_shape, data, 0xFFFFFFFF);
			if (myMap[j][i] == '0' || (mode == 0 && myMap[j][i] == 'P'))
				draw_rectangle( i * data->size_shape, j * data->size_shape, data, 0x000000FF);
            if(myMap[j][i] == 'P' && mode)
            {
				draw_rectangle(i * data->size_shape, j * data->size_shape, data, 0x000000FF);
				mlx_put_pixel(data->img, data->px = (i * data->size_shape) + 13, data->py = (j * data->size_shape) + 13, 0xFF0000FF);
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
        x = data->px + (cos(to_rad(data->angle)) * move_step_v);
        y = data->py + (sin(to_rad(data->angle)) * move_step_v);

    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        x = data->px - (cos(to_rad(data->angle)) * move_step_v);
        y = data->py - (sin(to_rad(data->angle)) * move_step_v);

    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        x = data->px - cos(to_rad(90) - to_rad(data->angle)) * move_step_v;
	    y = data->py + sin(to_rad(90) - to_rad(data->angle)) * move_step_v;

    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        x = data->px + cos(to_rad(90) - to_rad(data->angle)) * move_step_v;
	    y = data->py - sin(to_rad(90) - to_rad(data->angle)) * move_step_v;
    }
    if(myMap[(int)(y / data->size_shape)][(int)(x / data->size_shape)] == '1' 
        || (myMap[(int)(y / data->size_shape)][(int)(data->px / data->size_shape)] == '1' 
        && myMap[(int)(data->py / data->size_shape)][(int)(x / data->size_shape)] == '1'))
        return 0;
    return 1;
}

float   distance_between_points(float x1, float y1, float x2, float y2)
{
    return  (sqrt(pow((x2 - x1), 2) +  pow((y1 - y2), 2)));
}

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

void    check_rays_draw(t_cub3d *data, float ray_angle, int id_ray)
{
 
float hores_inters_x;
float hores_inters_y;
float next_hor_inters_x;
float next_hor_inters_y;
float step_hor_x;
float step_hor_y;
// horisontal down
if(ray_angle > 0 && ray_angle  < 180)
{
    hores_inters_y = floor((data->py / data->size_shape) + 1) * data->size_shape;
    hores_inters_x = data->px + (hores_inters_y - data->py) / tan(to_rad(ray_angle));
    next_hor_inters_y = hores_inters_y + data->size_shape;
    next_hor_inters_x =  hores_inters_x + ((next_hor_inters_y - hores_inters_y) / tan(to_rad(ray_angle))) ;
    step_hor_y = data->size_shape;
    step_hor_x = next_hor_inters_x - hores_inters_x;
    while (((int)(hores_inters_x / data->size_shape)) < data->width_map && ((int)(hores_inters_y / data->size_shape)) < data->height_map
        && hores_inters_x >= 0 && hores_inters_y >= 0 && myMap[(int)(hores_inters_y / data->size_shape)][(int)(hores_inters_x / data->size_shape)] != '1' )
    {
        hores_inters_y += step_hor_y;
        hores_inters_x += step_hor_x;
    }
}

// // horizontal  up
else
{
    hores_inters_y = floor((data->py / data->size_shape)) * data->size_shape;
    hores_inters_x = data->px - ((data->py - hores_inters_y) / tan(to_rad(ray_angle)));
    next_hor_inters_y = hores_inters_y - data->size_shape;
    next_hor_inters_x =  hores_inters_x - ((hores_inters_y - next_hor_inters_y) / tan(to_rad(ray_angle))) ;
    step_hor_y = data->size_shape;
    step_hor_x = next_hor_inters_x - hores_inters_x;

    while (((int)(hores_inters_x / data->size_shape))  < data->width_map && ((int)((hores_inters_y - 1) / data->size_shape)) < data->height_map
        && hores_inters_x >= 0 && hores_inters_y >= 0 && myMap[(int)((hores_inters_y - 1) / data->size_shape)][(int)(hores_inters_x / data->size_shape)] != '1')
    {
        hores_inters_y -= step_hor_y;
        hores_inters_x += step_hor_x;
    }
}

float vertcl_inters_x;
float vertcl_inters_y;
float next_ver_inters_x;
float next_ver_inters_y;
float step_ver_x;
float step_ver_y;
// vertical right

if(ray_angle < 90 || ray_angle > 270)
{
    vertcl_inters_x = floor((data->px / data->size_shape) + 1) * data->size_shape;
    vertcl_inters_y = data->py - ((data->px - vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    next_ver_inters_x = vertcl_inters_x + data->size_shape;
    next_ver_inters_y = vertcl_inters_y - ((vertcl_inters_x - next_ver_inters_x) * tan(to_rad(ray_angle)));
    step_ver_x = data->size_shape;
    step_ver_y = next_ver_inters_y - vertcl_inters_y;
    while (((int)(vertcl_inters_x / data->size_shape)) < data->width_map && ((int)(vertcl_inters_y / data->size_shape)) < data->height_map
        && vertcl_inters_x >= 0 && vertcl_inters_y >= 0 && myMap[(int)(vertcl_inters_y / data->size_shape)][(int)(vertcl_inters_x / data->size_shape)] != '1' )
    {
        vertcl_inters_y += step_ver_y;
        vertcl_inters_x += step_ver_x;
    }
}
else
{
    vertcl_inters_x = floor((data->px / data->size_shape)) * data->size_shape;
    vertcl_inters_y = data->py - ((data->px - vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    next_ver_inters_x = vertcl_inters_x - data->size_shape;
    next_ver_inters_y = vertcl_inters_y - ((vertcl_inters_x - next_ver_inters_x) * tan(to_rad(ray_angle)));
    step_ver_x = data->size_shape;
    step_ver_y = next_ver_inters_y - vertcl_inters_y;
     while (((int)((vertcl_inters_x - 1) / data->size_shape))  < data->width_map && ((int)(vertcl_inters_y / data->size_shape)) < data->height_map
        && vertcl_inters_x >= 0 && vertcl_inters_y >= 0 && myMap[(int)(vertcl_inters_y / data->size_shape)][(int)((vertcl_inters_x - 1) / data->size_shape)] != '1' )
    {
        vertcl_inters_y += step_ver_y;
        vertcl_inters_x -= step_ver_x;
    }
}



float distance_horz = distance_between_points(data->px, data->py, hores_inters_x, hores_inters_y);
float distance_vert = distance_between_points(data->px, data->py, vertcl_inters_x, vertcl_inters_y);

float dist;

if(distance_horz < distance_vert)
{
    dist = distance_horz;
    if(ray_angle >= 180 && ray_angle<= 360)
        ray_casting(data, dist , ray_angle, id_ray, 0x00000088);
    else
        ray_casting(data, dist , ray_angle, id_ray, 0x88000088);
    draw_line_dda(data, data->px, data->py, hores_inters_x , hores_inters_y, 0xFF0000FF);
    // printf("ana  \n"); 
}
else
{
   dist = distance_vert;
   if(ray_angle >= 90 && ray_angle <= 270)
        ray_casting(data, dist , ray_angle, id_ray, 0xFF000088);
    else
        ray_casting(data, dist , ray_angle, id_ray, 0x00550088);
   draw_line_dda(data, data->px, data->py, vertcl_inters_x, vertcl_inters_y, 0xFF0000FF); 
}
 
}

void    draw_view_angle(t_cub3d *data)
{
    int i = 0;
    float ray_angle = data->angle - (view_angle / 2);
    if (ray_angle < 0)
        ray_angle = 360 + ray_angle;
    int id_ray = 0;
    while (i < data->number_rays)
    {
        if (ray_angle >= 360)
            ray_angle -= 360;
        check_rays_draw(data, ray_angle, id_ray);
        id_ray++;
        ray_angle += (view_angle / data->number_rays) ;
        i++;
    }
}
void draw_ceil_floor(t_cub3d *data)
{
    int i ;
    int j = 0;
    while (j < height_win)
    {
        i = 0;
        while (i < width_win)
        {
            if(j < height_win / 2)
                mlx_put_pixel(data->img, i, j, 0x0000FF88);
            else
                mlx_put_pixel(data->img, i, j, 0x00FF0088);
            i++;
        }
        j++;
    }
    
}

void       testmouse(double xp, double yp, void *param)
{
    t_cub3d *data = (t_cub3d *)param;
    
    if (xp >= 0 && xp <= width_win && yp >= 0 && yp <= height_win)
    {
        if(xp > data->old_x)
            data->angle++;
        else
            data->angle--;
        data->old_x = xp;
    }
    
    
}

void    draw(void   *param)
{
    t_cub3d *data = (t_cub3d *)param;
    int32_t  x;
    int32_t y;
    
    mlx_cursor_hook(data->mlx, testmouse, (void *)data);
    if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->angle += speed_rotate;
        if(data->angle >= 360)
            data->angle = 0;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
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
    
    draw_ceil_floor(data);
    draw_map(data, 0);
    draw_view_angle(data);
    mlx_put_pixel(data->img, data->px, data->py, 0xFF0000FF);
}

int main(int ac, char **av)
{
    t_cub3d     data;
    
    data.mlx = mlx_init(width_win, height_win, "cub3d", true);
    if(!data.mlx)
        return (1);
    init_data(&data);
    data.img_map = mlx_new_image(data.mlx, data.size_map, data.size_map);
    data.img = mlx_new_image(data.mlx, width_win, height_win);
    if(!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0)))
        return(1);
    (mlx_image_to_window(data.mlx, data.img_map, 0, 0));
    if(!data.img_map)
        return 1;
    
    draw_map(&data, 1);
    mlx_loop_hook(data.mlx, draw, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (0);
}
