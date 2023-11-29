/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:17:09 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/29 15:07:47 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	controle_angle(t_cub3d *data)
{
	mlx_cursor_hook(data->mlx, move_mouse, (void *)data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += SPEED_ROTATE;
		if (data->angle >= 360)
			data->angle -= 360;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= SPEED_ROTATE;
		if (data->angle <= 0)
			data->angle += 360;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
}

void	controle_player(t_cub3d *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && check_wall(data))
	{
		data->px = data->px + (cos(to_rad(data->angle)) * MOVE_STEP);
		data->py = data->py + (sin(to_rad(data->angle)) * MOVE_STEP);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S) && check_wall(data))
	{
		data->px = data->px - (cos(to_rad(data->angle)) * MOVE_STEP);
		data->py = data->py - (sin(to_rad(data->angle)) * MOVE_STEP);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && check_wall(data))
	{
		data->px = data->px - cos(to_rad(90) - to_rad(data->angle)) * MOVE_STEP;
		data->py = data->py + sin(to_rad(90) - to_rad(data->angle)) * MOVE_STEP;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) && check_wall(data))
	{
		data->px = data->px + cos(to_rad(90) - to_rad(data->angle)) * MOVE_STEP;
		data->py = data->py - sin(to_rad(90) - to_rad(data->angle)) * MOVE_STEP;
	}
}

void	check_wall_part_tow(t_cub3d *data, int *x, int *y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*x = data->px + (cos(to_rad(data->angle)) * MOVE_STEP_V);
		*y = data->py + (sin(to_rad(data->angle)) * MOVE_STEP_V);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*x = data->px - (cos(to_rad(data->angle)) * MOVE_STEP_V);
		*y = data->py - (sin(to_rad(data->angle)) * MOVE_STEP_V);
	}
}

int	check_wall(t_cub3d *data)
{
	int	x;
	int	y;

	check_wall_part_tow(data, &x, &y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		x = data->px - cos(to_rad(90) - to_rad(data->angle)) * MOVE_STEP_V;
		y = data->py + sin(to_rad(90) - to_rad(data->angle)) * MOVE_STEP_V;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		x = data->px + cos(to_rad(90) - to_rad(data->angle)) * MOVE_STEP_V;
		y = data->py - sin(to_rad(90) - to_rad(data->angle)) * MOVE_STEP_V;
	}
	if (data->map[(int)(y / data->size_shape)]
		[(int)(x / data->size_shape)] == '1'
		|| (data->map[(int)(y / data->size_shape)][(int)(data->px
				/ data->size_shape)] == '1' && data->map[(int)(data->py
				/ data->size_shape)][(int)(x / data->size_shape)] == '1'))
		return (0);
	return (1);
}
