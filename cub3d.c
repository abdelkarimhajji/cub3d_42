/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 12:49:44 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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



                              

void    check_wall_part_tow(t_cub3d *data, int *x, int *y)
{
    if(mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        *x = data->px + (cos(to_rad(data->angle)) * move_step_v);
        *y = data->py + (sin(to_rad(data->angle)) * move_step_v);

    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        *x = data->px - (cos(to_rad(data->angle)) * move_step_v);
        *y = data->py - (sin(to_rad(data->angle)) * move_step_v);

    }
}

int    check_wall(t_cub3d *data)
{
    int x;
    int y;
    
    check_wall_part_tow(data, &x, &y);
    if(mlx_is_key_down(data->mlx, MLX_KEY_D))
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





void    check_ray_draw_down(t_cub3d *data, float ray_angle, int id_ray)
{
        data->hores_inters_y = floor((data->py / data->size_shape) + 1) * data->size_shape;
        data->hores_inters_x = data->px + 
        (data->hores_inters_y - data->py) / tan(to_rad(ray_angle));
        data->next_hor_inters_y = data->hores_inters_y + data->size_shape;
        data->next_hor_inters_x =  data->hores_inters_x + 
        ((data->next_hor_inters_y - data->hores_inters_y) / tan(to_rad(ray_angle))) ;
        data->step_hor_y = data->size_shape;
        data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
        while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
            && ((int)(data->hores_inters_y / data->size_shape)) < data->height_map
            && data->hores_inters_x >= 0 && data->hores_inters_y >= 0
            && myMap[(int)(data->hores_inters_y / data->size_shape)]
            [(int)(data->hores_inters_x / data->size_shape)] != '1' )
        {
            data->hores_inters_y += data->step_hor_y;
            data->hores_inters_x += data->step_hor_x;
        }
}

void    check_ray_draw_up(t_cub3d *data, float ray_angle, int id_ray)
{
    data->hores_inters_y = floor((data->py / data->size_shape)) * data->size_shape;
    data->hores_inters_x = data->px -
    ((data->py - data->hores_inters_y) / tan(to_rad(ray_angle)));
    data->next_hor_inters_y = data->hores_inters_y - data->size_shape;
    data->next_hor_inters_x =  data->hores_inters_x -
    ((data->hores_inters_y - data->next_hor_inters_y) / tan(to_rad(ray_angle))) ;
    data->step_hor_y = data->size_shape;
    data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;

    while (((int)(data->hores_inters_x / data->size_shape))  < data->width_map
        && ((int)((data->hores_inters_y - 1) / data->size_shape)) < data->height_map
        && data->hores_inters_x >= 0 && data->hores_inters_y >= 0
        && myMap[(int)((data->hores_inters_y - 1) / data->size_shape)]
        [(int)(data->hores_inters_x / data->size_shape)] != '1')
    {
        data->hores_inters_y -= data->step_hor_y;
        data->hores_inters_x += data->step_hor_x;
    }
}

void    check_ray_draw_right(t_cub3d *data, float ray_angle, int id_ray)
{
    data->vertcl_inters_x = floor((data->px / data->size_shape) + 1) * data->size_shape;
    data->vertcl_inters_y = data->py -
    ((data->px - data->vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    data->next_ver_inters_x = data->vertcl_inters_x + data->size_shape;
    data->next_ver_inters_y = data->vertcl_inters_y -
    ((data->vertcl_inters_x - data->next_ver_inters_x) * tan(to_rad(ray_angle)));
    data->step_ver_x = data->size_shape;
    data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
    while (((int)(data->vertcl_inters_x / data->size_shape)) < data->width_map 
    && ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
        && data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0 
        && myMap[(int)(data->vertcl_inters_y / data->size_shape)][(int)
        (data->vertcl_inters_x / data->size_shape)] != '1' )
    {
        data->vertcl_inters_y += data->step_ver_y;
        data->vertcl_inters_x += data->step_ver_x;
    }
}

void    check_ray_draw_left(t_cub3d *data, float ray_angle, int id_ray)
{
    data->vertcl_inters_x = floor((data->px / data->size_shape)) * data->size_shape;
    data->vertcl_inters_y = data->py -
    ((data->px - data->vertcl_inters_x) * tan(to_rad(ray_angle))) ;
    data->next_ver_inters_x = data->vertcl_inters_x - data->size_shape;
    data->next_ver_inters_y = data->vertcl_inters_y -
    ((data->vertcl_inters_x - data->next_ver_inters_x) * tan(to_rad(ray_angle)));
    data->step_ver_x = data->size_shape;
    data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
     while (((int)((data->vertcl_inters_x - 1) / data->size_shape))  < data->width_map 
     && ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
        && data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0 
        && myMap[(int)(data->vertcl_inters_y / data->size_shape)]
        [(int)((data->vertcl_inters_x - 1) / data->size_shape)] != '1' )
    {
        data->vertcl_inters_y += data->step_ver_y;
        data->vertcl_inters_x -= data->step_ver_x;
    }
}

void    calcul_distance(t_cub3d *data, float ray_angle, int id_ray)
{
    data->distance_horz = distance_between_points
        (data->px, data->py, data->hores_inters_x, data->hores_inters_y);
    data->distance_vert = distance_between_points
        (data->px, data->py, data->vertcl_inters_x, data->vertcl_inters_y);
}

void    call_raycasting(t_cub3d *data, float ray_angle, int id_ray)
{
    if(data->distance_horz < data->distance_vert)
    {
        if(ray_angle >= 180 && ray_angle<= 360)
            ray_casting(data, data->distance_horz , ray_angle, id_ray, 0x00000088);
        else
            ray_casting(data, data->distance_horz , ray_angle, id_ray, 0x88000088);
        draw_line_dda(data,  data->hores_inters_x , data->hores_inters_y, 0xFF0000FF);
    }
    else
    {
    if(ray_angle >= 90 && ray_angle <= 270)
            ray_casting(data, data->distance_vert , ray_angle, id_ray, 0xFF000088);
        else
            ray_casting(data, data->distance_vert , ray_angle, id_ray, 0x00550088);
    draw_line_dda(data,  data->vertcl_inters_x, data->vertcl_inters_y, 0xFF0000FF); 
    }
}

void    check_ray_draw(t_cub3d *data, float ray_angle, int id_ray)
{
    if(ray_angle > 0 && ray_angle  < 180)
        check_ray_draw_down(data, ray_angle, id_ray);
    else
        check_ray_draw_up(data, ray_angle, id_ray);
    if(ray_angle < 90 || ray_angle > 270)
        check_ray_draw_right(data, ray_angle, id_ray);
    else
        check_ray_draw_left(data, ray_angle, id_ray);
    calcul_distance(data, ray_angle, id_ray);
    call_raycasting(data, ray_angle, id_ray);
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


void    controle_angle(t_cub3d *data)
{
    mlx_cursor_hook(data->mlx, move_mouse, (void *)data);
    if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->angle += speed_rotate;
        if(data->angle >= 360)
            data->angle -= 360;
    }
    else if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->angle -= speed_rotate;
        if (data->angle <= 0)
            data->angle += 360;
    }
}

void    controle_player(t_cub3d *data)
{
    if(mlx_is_key_down(data->mlx, MLX_KEY_W) && check_wall(data))
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
}

void    draw(void   *param)
{
    t_cub3d *data = (t_cub3d *)param;
    
    controle_angle(data);
    controle_player(data);
    
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
