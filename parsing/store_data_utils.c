/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:34:51 by nachab            #+#    #+#             */
/*   Updated: 2023/11/29 12:23:09 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*remove_newline(char *str)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	trimmed = malloc((sizeof(char) * i) + 1);
	while (str[j] && str[j] != '\n')
	{
		trimmed[j] = str[j];
		j++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

int	check_which_texture(t_cub3d *data, int i, char *direction)
{
	if (ft_strnstr(data->file_content[i], 
			direction, ft_strlen(data->file_content[i])))
		return (1);
	return (0);
}
