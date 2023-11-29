/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:00:15 by nachab            #+#    #+#             */
/*   Updated: 2023/11/29 12:15:25 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*r_rgb_str(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 'F' && line[i] != 'C' && line[i] != ' '
			&& line[i] != '\t')
			return (&line[i]);
		i++;
	}
	return (NULL);
}

void	check_rgb_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]) && str[i][j] != '\n')
			{
				printf("Please fix the rgb values\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

long	rgb_to_hex(char *line)
{
	char	**values;
	long	hex_val;
	int		r;
	int		g;
	int		b;

	values = ft_split(line, ',');
	check_rgb_str(values);
	if (values && values[0] && values[1] && values[2])
	{
		r = ft_atoi(values[0]);
		g = ft_atoi(values[1]);
		b = ft_atoi(values[2]);
		free_2dchar_array(values);
		if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0
				&& b <= 255))
		{
			hex_val = ((long)r << 24) | ((long)g << 16) | (long)b << 8 | (1
					* 255);
			return (hex_val);
		}
	}
	return (-1);
}
