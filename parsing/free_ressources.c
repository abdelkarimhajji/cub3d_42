/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:47:32 by nachab            #+#    #+#             */
/*   Updated: 2023/12/10 12:54:16 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_2dchar_array(char **arr)
{
	char	**temp;
	int		i;

	temp = arr;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(arr);
}

void	free_images(t_cub3d *data)
{
	mlx_delete_image(data->mlx, data->textures.no_texture);
	mlx_delete_image(data->mlx, data->textures.so_texture);
	mlx_delete_image(data->mlx, data->textures.ea_texture);
	mlx_delete_image(data->mlx, data->textures.we_texture);
}

void	free_cub_data(t_cub3d *data)
{
	free_2dchar_array(data->file_content);
	free_2dchar_array(data->map);
	free_2dchar_array(data->tmp);
	free(data->map);
	free(data->tmp);
	free_images(data);
}

void	close_callback(void *param)
{
	if (param)
		exit(0);
	exit(0);
}
