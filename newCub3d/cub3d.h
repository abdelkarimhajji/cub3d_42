/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:19:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/24 11:45:48 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "./MLX/MLX42.h"

#define width_win  2000
#define height_win  900
#define size_shape 25

typedef struct s_cub3d
{
    mlx_t       *mlx;
    mlx_image_t *img;
    float       px;
    float       py;
    float       angle;
}               t_cub3d;
