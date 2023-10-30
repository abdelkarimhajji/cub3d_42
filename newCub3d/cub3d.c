/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/30 11:57:50 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


float   to_rad(float degree)
{
    return(degree * (M_PI / 180));
}

void draw_line_dda2(t_cub3d *data, double x1, double y1, double x2, double y2, uint32_t color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    double xIncrement = (double)dx / steps;
    double yIncrement = (double)dy / steps;

    double x = x1, y = y1;

    for (int i = 0; i <= steps; i++)
    {
		mlx_put_pixel(data->img, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
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
        mlx_put_pixel(data->img, round(x1), round(y1), color);
        x1 += increamentx;
        y1 += increamenty;        
        i++;
    }
}

void    init_data(t_cub3d *data)
{
    data->width_map = 15;
    data->height_map = 11;
    data->angle = 270;
    data->number_rays = width_win / wall_strip_width;
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
    if(myMap[(int)(y / size_shape)][(int)(x / size_shape)] == '1' 
        || (myMap[(int)(y / size_shape)][(int)(data->px / size_shape)] == '1' 
        && myMap[(int)(data->py / size_shape)][(int)(x / size_shape)] == '1'))
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
	height_wall = (25 * height_win) / dist;
	xstart = id_ray;
	xend = id_ray;
	ystart = (height_win / 2) - (height_wall / 2);
	yend = (height_win / 2) + (height_wall / 2);

    while (ystart < yend)
    {

        // if (xstart >= 0 && xstart < width_win && ystart >= 0 && ystart < height_win)
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
    hores_inters_y = floor((data->py / size_shape) + 1) * size_shape;
    hores_inters_x = data->px + (hores_inters_y - data->py) / tan(to_rad(ray_angle));
    next_hor_inters_y = hores_inters_y + size_shape;
    next_hor_inters_x =  hores_inters_x + ((next_hor_inters_y - hores_inters_y) / tan(to_rad(ray_angle))) ;
    step_hor_y = size_shape;
    step_hor_x = next_hor_inters_x - hores_inters_x;
    while (((int)(hores_inters_x / size_shape)) < data->width_map && ((int)(hores_inters_y / size_shape)) < data->height_map
        && hores_inters_x >= 0 && hores_inters_y >= 0 && myMap[(int)(hores_inters_y / size_shape)][(int)(hores_inters_x / size_shape)] != '1' )
    {
        hores_inters_y += step_hor_y;
        hores_inters_x += step_hor_x;
    }
}

// // horizontal  up
else
{
    hores_inters_y = floor((data->py / size_shape)) * size_shape;
    hores_inters_x = data->px - ((data->py - hores_inters_y) / tan(to_rad(ray_angle)));
    next_hor_inters_y = hores_inters_y - size_shape;
    next_hor_inters_x =  hores_inters_x - ((hores_inters_y - next_hor_inters_y) / tan(to_rad(ray_angle))) ;
    step_hor_y = size_shape;
    step_hor_x = next_hor_inters_x - hores_inters_x;

    while (((int)(hores_inters_x / size_shape))  < data->width_map && ((int)((hores_inters_y - 1) / size_shape)) < data->height_map
        && hores_inters_x >= 0 && hores_inters_y >= 0 && myMap[(int)((hores_inters_y - 1) / size_shape)][(int)(hores_inters_x / size_shape)] != '1')
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
    vertcl_inters_x = floor((data->px / size_shape) + 1) * size_shape;
    vertcl_inters_y = data->py - ((data->px - vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    next_ver_inters_x = vertcl_inters_x + size_shape;
    next_ver_inters_y = vertcl_inters_y - ((vertcl_inters_x - next_ver_inters_x) * tan(to_rad(ray_angle)));
    step_ver_x = size_shape;
    step_ver_y = next_ver_inters_y - vertcl_inters_y;
    while (((int)(vertcl_inters_x / size_shape)) < data->width_map && ((int)(vertcl_inters_y / size_shape)) < data->height_map
        && vertcl_inters_x >= 0 && vertcl_inters_y >= 0 && myMap[(int)(vertcl_inters_y / size_shape)][(int)(vertcl_inters_x / size_shape)] != '1' )
    {
        vertcl_inters_y += step_ver_y;
        vertcl_inters_x += step_ver_x;
    }
}
else
{
    vertcl_inters_x = floor((data->px / size_shape)) * size_shape;
    vertcl_inters_y = data->py - ((data->px - vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    next_ver_inters_x = vertcl_inters_x - size_shape;
    next_ver_inters_y = vertcl_inters_y - ((vertcl_inters_x - next_ver_inters_x) * tan(to_rad(ray_angle)));
    step_ver_x = size_shape;
    step_ver_y = next_ver_inters_y - vertcl_inters_y;
     while (((int)((vertcl_inters_x - 1) / size_shape))  < data->width_map && ((int)(vertcl_inters_y / size_shape)) < data->height_map
        && vertcl_inters_x >= 0 && vertcl_inters_y >= 0 && myMap[(int)(vertcl_inters_y / size_shape)][(int)((vertcl_inters_x - 1) / size_shape)] != '1' )
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
    // draw_line_dda(data, data->px, data->py, hores_inters_x , hores_inters_y, 0xFF0000FF);
    dist = distance_horz;
    if(ray_angle >= 180 && ray_angle<= 360)
        ray_casting(data, dist , ray_angle, id_ray, 0x00000088);
    else
        ray_casting(data, dist , ray_angle, id_ray, 0x88000088);
    // printf("ana  \n"); 
}
else
{
//    draw_line_dda(data, data->px, data->py, vertcl_inters_x, vertcl_inters_y, 0xFF0000FF); 
   dist = distance_vert;
   if(ray_angle >= 90 && ray_angle <= 270)
        ray_casting(data, dist , ray_angle, id_ray, 0xFF000088);
    else
        ray_casting(data, dist , ray_angle, id_ray, 0x00550088);
}
 
}

void    draw_view_angle(t_cub3d *data)
{
    int i = 0;
    float ray_angle = data->angle - (view_angle / 2);
    if (ray_angle < 0)
        ray_angle = 360 + ray_angle;
    int id_ray = 0;
    // printf("ray angle %f\n", ray_angle);
    while (i < data->number_rays)
    {
        if (ray_angle >= 360)
            ray_angle -= 360;
        check_rays_draw(data, ray_angle, id_ray);
        id_ray++;
        ray_angle += (view_angle / data->number_rays) ;
        i++;
    }
    // printf("ray angle %f\n", ray_angle);
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
        // printf("hi\n");
        j++;
    }
    
}

void    draw(void   *param)
{
    t_cub3d *data = (t_cub3d *)param;

    if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) )
    {
        data->angle += speed_rotate;
        if(data->angle >= 360)
            data->angle = 0;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT)  )
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
    // check_rays_draw(data, data->angle);
    draw_view_angle(data);
    draw_map(data, 0);
    mlx_put_pixel(data->img, data->px, data->py, 0xFF0000FF);
    // draw_line_dda(data, data->px, data->py, data->px + (cos(to_rad(data->angle)) * 100),
    //  data->py + (sin(to_rad(data->angle)) * 100), 0xFFFFFFFF);
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

//  if(ray_angle > 0 && ray_angle  < 180)
//     {
//         second_pointy = (int)((data->py / size_shape) + 1) * size_shape;
//         second_pointx =  data->px - ((data->py - second_pointy) / tan(to_rad(ray_angle)));
//         second_pointy2 = (second_pointy + size_shape);
//         second_pointx2 = second_pointx - ((second_pointy - second_pointy2) / tan(to_rad(ray_angle)));
//         // steph = (second_pointx2 - second_pointx) / cos(to_rad(data->angle));
//         steph = (second_pointx2 - second_pointx);
//         while (((int)(second_pointx / size_shape))  < (data->width_map - 1) &&  ((int)(second_pointy / size_shape))  < (data->height_map-1) && myMap[(int)(second_pointy / size_shape)][(int)(second_pointx / size_shape)] != '1')
//         {
//             second_pointy += size_shape;
//             second_pointx += steph;
//             printf("x %d\n", ((int)(second_pointx / size_shape)));
//             printf("y %d\n", ((int)(second_pointy / size_shape)));
//             if (((int)(second_pointx / size_shape))  > data->width_map)
//                 break;
//             if (((int)(second_pointy / size_shape))  > data->height_map)
//                 break;
//         }
    
//     }
//     else
//     {
//         second_pointy = (int)(data->py / size_shape) * size_shape;
//         second_pointx =  (((-1 * data->py) + second_pointy) / tan(to_rad(ray_angle))) + data->px;
//         second_pointy2 = (second_pointy - size_shape);
//         second_pointx2 = (((-1 * second_pointy) + second_pointy2) / tan(to_rad(ray_angle))) + second_pointx;
//         // steph = (second_pointx2 - second_pointx) / cos(to_rad(data->angle));
//         steph = (second_pointx2 - second_pointx);
//         while (myMap[(int)(second_pointy / size_shape)][(int)(second_pointx / size_shape)] != '1' &&
//             ((int)(second_pointx / size_shape)) < data->width_map && ((int)(second_pointy / size_shape)) < data->height_map)
//         {
//             second_pointy -= size_shape;
//             second_pointx += steph;
//         }
        
//     }
// // vertical 180

// if(ray_angle < 90 || ray_angle > 270)
// {
//     second_pointx2v = (int)((data->px / size_shape)  + 1) * size_shape;
//     second_pointy2v = (tan(to_rad(ray_angle)) * (second_pointx2v - data->px)) + data->py ;
// }
// else
// {
//     second_pointx2v = (int)((data->px / size_shape)) * size_shape;
//     second_pointy2v = (tan(to_rad(ray_angle)) * (data->px - second_pointx2v)) + data->py;
// }

// // vertical 0

// float lastar = sqrt(pow((data->py - second_pointy), 2) + pow((second_pointx - data->py), 2));
// float lastve = sqrt(pow((data->py - second_pointy2v), 2) + pow((second_pointx2v - data->py), 2));

//     if(lastar > lastve)
//         draw_line_dda(data, data->px, data->py, second_pointx2v, second_pointy2v, 0xFF0000FF);
//     else
//         draw_line_dda(data, data->px, data->py, second_pointx, second_pointy, 0xFF0000FF);
        
//     // second_pointy2 = ((((-1 * data->px) - second_pointx2) * tan(to_rad(data->angle))) - data->py);
//     // draw_line_dda(data, data->px, data->py, second_pointx2v, second_pointy2v, 0xFF0000FF);
//     // printf("angle => %f", data->angle);








   float   second_pointy;
    float   second_pointx;
    float   second_pointy2;
    float   second_pointx2;
    float   second_pointy2v;
    float   second_pointx2v;
    float   steph;

    // int ray_face_down = ray_angle > 0 && ray_angle  < 180;
    // int ray_face_up  = !ray_face_down;
    // int ray_face_right = ray_angle < 90 || ray_angle > 270;
    // int ray_face_left = !ray_face_right;
    
    // float xintercept, yintercept;
    // float xstep, ystep;

    // ///////////////////////////////////////////
    // // horizontal ray-grid intresection code //
    // ///////////////////////////////////////////
    
    // int found_horz_wall_hit = false;
    // float horz_wall_hitx = 0;
    // float horz_wall_hity = 0;
    // char horz_wall_content ;
    
    // // find the y-coordinate of the closest horizontal grid intesection 
    // yintercept = floor(data->py / size_shape) * size_shape;
    // yintercept += ray_face_down ? size_shape : 0;
    // // find the x-coordinate of the closest horzintal grid intesection
    
    // xintercept = data->px + (yintercept - data->py) / tan(to_rad(ray_angle));

    // // calculate the increment xstep and ystep
    // ystep = size_shape;
    // ystep *= ray_face_up ? -1 : 1;
    
    // xstep = size_shape / tan(to_rad(ray_angle));
    // xstep *= (ray_face_left && xstep > 0) ? -1 : 1;
    // xstep *= (ray_face_right && xstep < 0) ? -1 : 1;

    // float next_horiz_x = xintercept;
    // float next_horiz_y = yintercept;
    
    // while (next_horiz_x >= 0 && next_horiz_x <= data->width_map && next_horiz_y >= 0 && next_horiz_y <= data->height_map)
    // {
    //     float x_to_check = next_horiz_x;
    //     float y_to_check = next_horiz_y + (ray_face_up ? -1 : 0);
        
    //     if(myMap[(int)floor(y_to_check / size_shape)][(int)floor(x_to_check / size_shape)] == '1')
    //     {
    //         horz_wall_hitx = next_horiz_x;
    //         horz_wall_hity = next_horiz_y;
    //         horz_wall_content = myMap[(int)floor(y_to_check / size_shape)][(int)floor(x_to_check / size_shape)];
    //         found_horz_wall_hit = true;
    //         break;
    //     }else
    //     {
    //         next_horiz_x += xstep;
    //         next_horiz_y += ystep;
    //     }
    //     /* code */
    // }
    
    // ///////////////////////////////////////////
    // // Vertical ray-grid intresection code //
    // ///////////////////////////////////////////
    
    // int found_verz_wall_hit = false;
    // float verz_wall_hitx = 0;
    // float verz_wall_hity = 0;
    // char verz_wall_content ;
    
    // // find the x-coordinate of the closest verizontal grid intesection 
    // xintercept = floor(data->px / size_shape) * size_shape;
    // xintercept += ray_face_right ? size_shape : 0;
    
    // // find the y-coordinate of the closest verzintal grid intesection
    
    // yintercept = data->py + (xintercept - data->px) * tan(to_rad(ray_angle));

    // // calculate the increment xstep and ystep
    // xstep = size_shape;
    // xstep *= ray_face_left ? -1 : 1;
    
    // ystep = size_shape * tan(to_rad(ray_angle));
    // ystep *= (ray_face_up && ystep > 0) ? -1 : 1;
    // ystep *= (ray_face_down && ystep < 0) ? -1 : 1;

    // float next_veriz_x = xintercept;
    // float next_veriz_y = yintercept;
    
    // while (next_veriz_x >= 0 && next_veriz_x <= data->width_map && next_veriz_y >= 0 && next_veriz_y <= data->height_map)
    // {
    //     float x_to_check = next_veriz_x + (ray_face_left ? -1 : 0);
    //     float y_to_check = next_veriz_y;
        
    //     if(myMap[(int)floor(y_to_check / size_shape)][(int)floor(x_to_check / size_shape)] == '1')
    //     {
    //         verz_wall_hitx = next_veriz_x;
    //         verz_wall_hity = next_veriz_y;
    //         found_verz_wall_hit = true;
    //         break;
    //     }else
    //     {
    //         next_veriz_x += xstep;
    //         next_veriz_y += ystep;
    //     }
    //     /* code */
    // }

    // // calculate both horizontal and vertical hit distances and  choose  the  small  one 
    // float horz_hit_distance = found_horz_wall_hit
    //     ? distance_between_points(data->px, data->py, horz_wall_hitx, horz_wall_hity)
    //     : INT_MAX;
    // float vert_hit_distance = found_verz_wall_hit
    //     ? distance_between_points(data->px, data->py, verz_wall_hitx, verz_wall_hity)
    //     : INT_MAX;

    // if(vert_hit_distance < horz_hit_distance)
    // {
    //     draw_line_dda(data, data->px, data->py, verz_wall_hitx, verz_wall_hity, 0xFF0000FF);
    // }
    // else
    // {
    //     draw_line_dda(data, data->px, data->py, horz_wall_hitx, horz_wall_hity, 0xFF0000FF);
    // }
