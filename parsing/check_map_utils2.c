/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:59:24 by nachab            #+#    #+#             */
/*   Updated: 2023/12/10 17:37:42 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stddef.h>

size_t	get_index(char *line, char *needle)
{
	size_t	i;

	i = 0;
	while (*line && line != needle)
	{
		line++;
		i++;
	}
	return (i);
}

size_t	line_length(char *line, char *pos)
{
	size_t	i;

	i = 0;
	while (line[i] && &line[i] != pos)
	{
		i++;
	}
	return (i + 1);
}

int	valid_cell_path(t_cub3d *game, int y, int x)
{
	char	pos;
	size_t	length;

	pos = game->player.direction;
	if (game->tmp[y][x] == ' ' || ((game->tmp[y][x] == '0' || game->tmp[y][x] 
			== pos) && y == 0) 
		|| ((game->tmp[y][x] == '0' || game->tmp[y][x] == 
			pos) && game->tmp[y + 1] == NULL) 
		|| ((game->tmp[y][x] == '0' || game->tmp[y][x] 
			== pos) && x == 0) 
		|| ((game->tmp[y][x] == '0' || game->tmp[y][x] 
			== pos) && (game->tmp[y][x + 1] == '\n' 
		|| game->tmp[y][x + 1] == '\0')))
	{
		return (1);
	}
	length = line_length(game->tmp[y], &game->tmp[y][x]);
	if (y > 0 && length > ft_strlen(game->tmp[y - 1]))
		return (1);
	else if (game->tmp[y + 1] && length > ft_strlen(game->tmp[y + 1]))
		return (1);
	return (0);
}

void	check_valid_path(t_cub3d *game, int y, int x)
{
	if (valid_cell_path(game, y, x))
	{
		printf("Map path isn't valid\n");
		exit (1);
	}
	else if (game->tmp[y][x] == 'V' || game->tmp[y][x] == '1')
		return ;
	else if (game->tmp[y][x] == game->player.direction 
		|| game->tmp[y][x] == '0')
	{
		game->tmp[y][x] = 'V';
		check_valid_path(game, y, x + 1);
		if (x > 0)
			check_valid_path(game, y, x - 1);
		if (game->tmp[y + 1] != NULL)
			check_valid_path(game, y + 1, x);
		if (y > 0)
			check_valid_path(game, y - 1, x);
	}
}

void	valid_texture_line(char *str, char *needle)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], needle, ft_strlen(needle)) == 0)
		{
			i += 2;
			break ;
		}
		else if (str[i] != ' ' && str[i] != '\t')
			exit (1);
		i++;
	}
	while (str[i])
	{
		if (ft_strncmp(&str[i], "textures", ft_strlen("textures")) == 0 
			|| ft_strncmp(&str[i], "./textures", ft_strlen("./textures")) == 0 
			|| ft_strncmp(&str[i], ".textures", ft_strlen(".textures")) == 0)
			return ;
		else if (str[i] != ' ' && str[i] != '\t')
			exit (1);
		i++;
	}
}
