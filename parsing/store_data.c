/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:00:18 by nachab            #+#    #+#             */
/*   Updated: 2023/11/30 13:09:20 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	store_texture(t_cub3d *data, int i)
{
	if (check_which_texture(data, i, "NO"))
	{
		data->paths.no_path = remove_newline(ft_strnstr(data->file_content[i],
					"textures", ft_strlen(data->file_content[i])));
	}
	else if (check_which_texture(data, i, "SO"))
	{
		data->paths.so_path = remove_newline(ft_strnstr(data->file_content[i],
					"textures", ft_strlen(data->file_content[i])));
	}
	else if (check_which_texture(data, i, "EA"))
	{
		data->paths.ea_path = remove_newline(ft_strnstr(data->file_content[i],
					"textures", ft_strlen(data->file_content[i])));
	}
	else if (check_which_texture(data, i, "WE"))
	{
		data->paths.we_path = remove_newline(ft_strnstr(data->file_content[i],
					"textures", ft_strlen(data->file_content[i])));
	}
	else if (ft_strchr(data->file_content[i], 'F'))
		data->textures.floor_hex = rgb_to_hex(r_rgb_str(data->file_content[i]));
	else if (ft_strchr(data->file_content[i], 'C'))
		data->textures.sky_hex = rgb_to_hex(r_rgb_str(data->file_content[i]));
}

int	store_textures_path(t_cub3d *data, int length)
{
	int	i;

	i = 0;
	while (data->file_content[i] != NULL && i < length)
	{
		store_texture(data, i);
		i++;
	}
	if (check_path_rgb(data) == 0)
		return (0);
	exit(1);
}

void	init_textures(mlx_t *mlx, t_cub3d *data)
{
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*we_texture;

	no_texture = mlx_load_png(data->paths.no_path);
	so_texture = mlx_load_png(data->paths.so_path);
	ea_texture = mlx_load_png(data->paths.ea_path);
	we_texture = mlx_load_png(data->paths.we_path);
	if (!no_texture || !so_texture || !we_texture || !ea_texture)
	{
		printf("Wasn't able to initialize the textures\n");
		exit(1);
	}
	data->textures.no_texture = mlx_texture_to_image(mlx, no_texture);
	data->textures.so_texture = mlx_texture_to_image(mlx, so_texture);
	data->textures.ea_texture = mlx_texture_to_image(mlx, ea_texture);
	data->textures.we_texture = mlx_texture_to_image(mlx, we_texture);
	mlx_delete_texture(no_texture);
	mlx_delete_texture(so_texture);
	mlx_delete_texture(ea_texture);
	mlx_delete_texture(we_texture);
}

int	map_length(t_cub3d *data, int index)
{
	int	i;

	i = 0;
	while (data->file_content[index] != NULL)
	{
		i++;
		index++;
	}
	return (i);
}

int	store_map(t_cub3d *data, int index)
{
	int	i;

	i = 0;
	while (data->file_content[index] != NULL
		&& (empty_line(data->file_content[index]) == 0))
		index++;
	data->map = malloc((map_length(data, index) + 1) * sizeof(char *));
	while (data->file_content[index] != NULL)
	{
		data->map[i] = data->file_content[index];
		i++;
		index++;
	}
	data->map[i] = NULL;
	return (0);
}
