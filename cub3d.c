/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/12/10 13:09:44 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_cub3d *data)
{
	data->map[data->player.i][data->player.j] = 'P';
	if (data->player.direction == 'N')
		data->angle = 270;
	else if (data->player.direction == 'S')
		data->angle = 90;
	else if (data->player.direction == 'W')
		data->angle = 180;
	else
		data->angle = 0;
	data->number_rays = WIDTH_WIN;
	if (WIDTH_WIN / 9 > HEIGHT_WIN / 9)
		data->size_map = WIDTH_WIN / 9;
	else
		data->size_map = HEIGHT_WIN / 9;
	if (data->height_map > data->width_map)
		data->size_shape = data->size_map / data->height_map;
	else
		data->size_shape = data->size_map / data->width_map;
	data->old_x = WIDTH_WIN;
}

void	calcul_distance(t_cub3d *data)
{
	data->distance_horz = distance_between_points(data->px, data->py,
			data->hores_inters_x, data->hores_inters_y);
	data->distance_vert = distance_between_points(data->px, data->py,
			data->vertcl_inters_x, data->vertcl_inters_y);
}

void	check_ray_draw(t_cub3d *data, float ray_angle, int id_ray)
{
	if (ray_angle > 0 && ray_angle < 180)
		check_ray_draw_down(data, ray_angle);
	else
		check_ray_draw_up(data, ray_angle);
	if (ray_angle < 90 || ray_angle > 270)
		check_ray_draw_right(data, ray_angle);
	else
		check_ray_draw_left(data, ray_angle);
	calcul_distance(data);
	call_raycasting(data, ray_angle, id_ray);
}

void	draw(void *param)
{
	t_cub3d	*data;

	data = (t_cub3d *)param;
	controle_angle(data);
	controle_player(data);
	draw_ceil_floor(data);
	draw_map(data, 0);
	draw_view_angle(data);
	mlx_put_pixel(data->img, data->px, data->py, 0xFF0000FF);
}

int	main(int ac, char **av)
{
	t_cub3d	data;

	if (ac != 2)
		return (printf("Please provide a map file with .cub"),
			printf(" extenstion in the maps directory\n"), EXIT_FAILURE);
	init_game(av[1], &data);
	data.mlx = mlx_init(WIDTH_WIN, HEIGHT_WIN, "cub3d", false);
	if (!data.mlx)
		return (1);
	init_textures(data.mlx, &data);
	init_data(&data);
	data.img_map = mlx_new_image(data.mlx, data.size_map, data.size_map);
	data.img = mlx_new_image(data.mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0)))
		return (1);
	(mlx_image_to_window(data.mlx, data.img_map, 0, 0));
	if (!data.img_map)
		return (1);
	draw_map(&data, 1);
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_close_hook(data.mlx, close_callback, NULL);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_cub_data(&data);
	return (0);
}
