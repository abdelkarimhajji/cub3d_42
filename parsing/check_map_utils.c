#include "../cub3d.h"

int is_map_line(char *line)
{
    while (*line)
    {
        if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ' && *line != '\t' && *line != '\n')
            return (1);
        line++;
    }
    return (0);
}


// returns 1 if line isn't empty
int empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (1);
        i++;
    }
    return (0);
}

void    check_map(t_cub3d *data)
{
    int i;

    i = 0;
    while (data->map[i] != NULL)
    {
        if (is_map_line(data->map[i]) == 1 || !empty_line(data->map[i])) {
            printf("Error, Map can only be composed of 01NSWE.\n");
            exit(1);
        }
        i++;
    }
}

void    check_dimensions(t_cub3d *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
            j++;
        if (j > 30)
        {
            printf("Column width surpassed (max 30)\n");
            exit (1);
        }
        i++;
    }
    if (i > 30)
    {
        printf("Row height surpassed (max 20)");
        exit (1);
    }
}

void    check_walls(t_cub3d *data)
{
    int i;
    int j;
    
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
        {
            if (i == 0 || data->map[i + 1] == NULL)
            {
                if (data->map[i][j] != '1')
                    exit (1);
            }
            else if (j == 0 || data->map[i][j + 1] == '\n')
            {
                if (data->map[i][j] != '1')
                    exit (1);
            }
            j++;
        }
        i++;
    }
}

size_t get_index(char *line, char *needle)
{
    size_t i;

    i = 0;
    while (*line && line != needle)
    {
        line++;
        i++;
    }
    return (i);
}

int check_cells(t_cub3d *data, int i, int j)
{
    if ((data->map[i][j + 1] != '0' && data->map[i][j + 1] != data->player.direction && data->map[i][j + 1] != '1'))
    {
        return (1);
    }
    else if ((data->map[i][j - 1] != '0' && data->map[i][j - 1] != data->player.direction && data->map[i][j - 1] != '1'))
    {
        return (1);
    }
    else if ((data->map[i + 1][j] != '0' && data->map[i + 1][j] != data->player.direction && data->map[i + 1][j] != '1') || get_index(data->map[i], &data->map[i][j]) > ft_strlen(data->map[i + 1]))
    {
        return (1);
    }
    else if ((data->map[i - 1][j] != '0' && data->map[i - 1][j] != data->player.direction && data->map[i - 1][j] != '1') || get_index(data->map[i], &data->map[i][j]) > ft_strlen(data->map[i - 1]))
    {
        return (1);
    }
    return (0);
}

void    check_valid_path(t_cub3d *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
        {
            if ((i > 0 && j > 0) && (data->map[i][j] == data->player.direction || data->map[i][j] == '0') && (data->map[i + 1] != NULL))
            {
                if (check_cells(data, i, j) == 1)
                {
                    printf("Map path isn't valid\n");
                    exit (1);
                }
            }
            j++;
        }
        i++;
    }
}