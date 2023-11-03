/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:19:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 12:41:29 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "./MLX/MLX42.h"

#define width_win  2000
#define height_win  900
#define speed_rotate 0.5
#define move_step 0.2
#define move_step_v 0.6
#define view_angle 60

static char myMap[12][30] = {
    "111111111111111111111111111111",
    "100000001010101000110001     1",
    "100000010001001000100001     1",
    "111110000100110101100001     1",
    "1000001P0001010000000001     1",
    "100000000111110000000001     1",
    "100000100000000001111001     1",
    "100000010000000000000001     1",
    "100000001111110000011111     1",
    "111111111111001110000001     1",
    "1         00110001111111     1",
    "                              "
};




typedef struct s_cub3d
{
    mlx_t       *mlx;
    mlx_image_t *img;
    mlx_image_t *img_map;
    int         width_map;
    int         height_map;
    int         size_map;
    int         size_shape;
    float       px;
    float       py;
    float       angle;
    float       number_rays;
    mlx_texture_t *load_img;
    double      old_x;
    float hores_inters_x;
    float hores_inters_y;
    float next_hor_inters_x;
    float next_hor_inters_y;
    float step_hor_x;
    float step_hor_y;
    float distance_horz;
    float distance_vert;
    float vertcl_inters_x;
    float vertcl_inters_y;
    float next_ver_inters_x;
    float next_ver_inters_y;
    float step_ver_x;
    float step_ver_y;
    float   steps;
    float   increamentx;
    float   increamenty;
}               t_cub3d;

float   to_rad(float degree);
void    draw_line_dda(t_cub3d *data, float  x2, float  y2, uint32_t color);
float   distance_between_points(float x1, float y1, float x2, float y2);
void draw_map(t_cub3d *data, int mode);
void    draw_view_angle(t_cub3d *data);
void    check_ray_draw(t_cub3d *data, float ray_angle, int id_ray);
void ray_casting(t_cub3d *data, float dist, float ray_angle, int id_ray, int color);
void       move_mouse(double xp, double yp, void *param);

#endif