/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:59:37 by nachab            #+#    #+#             */
/*   Updated: 2023/12/10 13:44:32 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(char *file, char *extension)
{
	char	*file_extension;

	file_extension = ft_strchr(file, '.');
	if (file_extension != NULL && 
		ft_strncmp(file_extension, "./maps", 6) == 0)
	{
		file_extension++;
		file_extension = ft_strchr(file_extension, '.');
	}
	if (file_extension != NULL)
	{
		if (ft_strncmp(file_extension, extension, ft_strlen(extension)
				+ 1) == 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	parse_file_content(t_cub3d *data)
{
	int	v;
	int	i;

	i = 0;
	v = 0;
	while (data->file_content[i] != NULL)
	{
		if (empty_line(data->file_content[i]))
			v++;
		if (v == 6)
			break ;
		i++;
	}
	if (store_textures_path(data, ++i) == 0)
	{
		store_map(data, i);
		check_map(data);
	}
	else
	{
		printf("Error, Textures needed weren't provided.\n");
		exit(1);
	}
}
