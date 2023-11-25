#include "../cub3d.h"

char    *return_rgb_string(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != 'F' && line[i] != 'C' && line[i] != ' ' && line[i] != '\t')
            return (&line[i]);
        i++;
    }
    return (NULL);
}

long    rgb_to_hex(char *line) 
{
    char    **values;
    int     r;
    int     g;
    int     b;

    values = ft_split(line, ',');
    if (values && values[0] && values[1] && values[2])
    {
        r = ft_atoi(values[0]);
        g = ft_atoi(values[1]);
        b = ft_atoi(values[2]);
        if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
        {
            long hex_val = ((long)r << 16) | ((long)g << 8) | (long)b;
            return (hex_val);
        }
    }
    return (-1);
}