#include "../cub3d.h"

static char *trim_newline(char *str) {
    int i;
    int j;
    char *trimmed;

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

int store_textures_path(t_cub3d *data, int length) 
{
    int i;

    i = 0;
    while (data->file_content[i] != NULL && i < length)
    {
        if (ft_strnstr(data->file_content[i], "NO", ft_strlen(data->file_content[i]))) {
            data->paths.no_path = trim_newline(ft_strnstr(data->file_content[i], "textures", ft_strlen(data->file_content[i])));
        }
        else if (ft_strnstr(data->file_content[i], "SO", ft_strlen(data->file_content[i]))) {
            data->paths.so_path = trim_newline(ft_strnstr(data->file_content[i], "textures", ft_strlen(data->file_content[i])));
        }
        else if (ft_strnstr(data->file_content[i], "WE", ft_strlen(data->file_content[i]))) {
            data->paths.we_path = trim_newline(ft_strnstr(data->file_content[i], "textures", ft_strlen(data->file_content[i])));
        }
        else if (ft_strnstr(data->file_content[i], "EA", ft_strlen(data->file_content[i]))) {
            data->paths.ea_path = trim_newline(ft_strnstr(data->file_content[i], "textures", ft_strlen(data->file_content[i])));
        }
        else if (ft_strchr(data->file_content[i], 'F'))
            data->textures.floor_hex = rgb_to_hex(return_rgb_string(data->file_content[i]));
        else if (ft_strchr(data->file_content[i], 'C'))
            data->textures.sky_hex = rgb_to_hex(return_rgb_string(data->file_content[i]));
        i++;
    }
    if (check_path_rgb(data) == 0)
        return (0);
    exit (1);
}

void    init_textures(mlx_t *mlx, t_cub3d *data)
{

    mlx_texture_t *no_texture;
    mlx_texture_t *so_texture;
    mlx_texture_t *ea_texture;
    mlx_texture_t *we_texture;

    no_texture = mlx_load_png(data->paths.no_path);
    so_texture = mlx_load_png(data->paths.so_path);
    ea_texture = mlx_load_png(data->paths.ea_path);
    we_texture = mlx_load_png(data->paths.we_path);
    if (!no_texture || !so_texture || !we_texture || !ea_texture)
    {
        printf("Wasn't able to initialize the textures\n");
        exit (1);
    }
    data->textures.no_texture = mlx_texture_to_image(mlx, no_texture);
    data->textures.so_texture = mlx_texture_to_image(mlx, so_texture);
    data->textures.ea_texture = mlx_texture_to_image(mlx, ea_texture);
    data->textures.we_texture = mlx_texture_to_image(mlx, we_texture);
}

int map_length(t_cub3d *data, int index)
{
    int i;

    i = 0;
    while (data->file_content[index] != NULL)
    {
        i++;
        index++;
    }
    return (i);
}

int    store_map(t_cub3d *data, int index)
{
    int i;

    i = 0;
    while (data->file_content[index] != NULL && (empty_line(data->file_content[index]) == 0))
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