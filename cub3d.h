/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:19:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/25 13:45:21 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX/MLX42.h"
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include  <fcntl.h>

# define WIDTH_WIN 2000
# define HEIGHT_WIN 900
# define SPEED_ROTATE 0.5
# define MOVE_STEP 0.2
# define MOVE_STEP_V 0.6
# define VIEW_ANGLE 60

static char			myMap[12][30] = {"111111111111111111111111111111",
				"100000001010101000110001     1",
				"100000010001001000100001     1",
				"111110000100110101100001     1",
				"1000001P0001010000000001     1",
				"100000000111110000000001     1",
				"100000100000000001111001     1",
				"100000010000000000000001     1",
				"100000001111110000011111     1",
				"111111111111001110000001     1",
				"1         00110001111111     1",
				"                              "};

typedef struct s_paths {
    char        *no_path;
    char        *so_path;
    char        *we_path;
    char        *ea_path;
} t_paths;

typedef struct  s_textures {
    mlx_image_t    *no_texture;
    mlx_image_t    *so_texture;
    mlx_image_t    *we_texture;
    mlx_image_t    *ea_texture;
    long   sky_hex;
    long   floor_hex;
} t_textures;

typedef struct s_player {
    int     i;
    int     j;
    char    direction;
} t_player;

typedef struct s_cub3d
{
	// Nassim stuff
	char        	**file_content;
    char        	**map;
	t_paths			paths;
	t_textures  	textures;
    t_player    	player;
	// Abdlkrim stuff
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*img_map;
	int				width_map;
	int				height_map;
	int				size_map;
	int				size_shape;
	float			px;
	float			py;
	float			angle;
	float			number_rays;
	mlx_texture_t	*load_img;
	double			old_x;
	float			hores_inters_x;
	float			hores_inters_y;
	float			next_hor_inters_x;
	float			next_hor_inters_y;
	float			step_hor_x;
	float			step_hor_y;
	float			distance_horz;
	float			distance_vert;
	float			dist;
	float			vertcl_inters_x;
	float			vertcl_inters_y;
	float			next_ver_inters_x;
	float			next_ver_inters_y;
	float			step_ver_x;
	float			step_ver_y;
	float			steps;
	float			increamentx;
	float			increamenty;
	float			presentTexture;
}					t_cub3d;

float				to_rad(float degree);
void				draw_line_dda(t_cub3d *data, float x2, float y2,
						uint32_t color);
float				distance_between_points(float x1, float y1, float x2,
						float y2);
void				draw_map(t_cub3d *data, int mode);
void				draw_VIEW_ANGLE(t_cub3d *data);
void				check_ray_draw(t_cub3d *data, float ray_angle, int id_ray);
void	ray_casting(t_cub3d *data, float ray_angle, int id_ray, mlx_image_t *img);
void				move_mouse(double xp, double yp, void *param);
void				draw_ceil_floor(t_cub3d *data);
void				controle_angle(t_cub3d *data);
void				controle_player(t_cub3d *data);
void				check_wall_part_tow(t_cub3d *data, int *x, int *y);
int					check_wall(t_cub3d *data);
void				check_ray_draw(t_cub3d *data, float ray_angle, int id_ray);
void				check_ray_draw_down(t_cub3d *data, float ray_angle,
						int id_ray);
void				check_ray_draw_up(t_cub3d *data, float ray_angle,
						int id_ray);
void				check_ray_draw_right(t_cub3d *data, float ray_angle,
						int id_ray);
void				check_ray_draw_left(t_cub3d *data, float ray_angle,
						int id_ray);
void				call_raycasting(t_cub3d *data, float ray_angle, int id_ray);


#define SUCCESS 1
#define FAILURE -1

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// void    init_struct(t_game_data *game_data);
void    init_textures(mlx_t *mlx, t_cub3d *data);
int     check_extension(char *file, char *extension);
void    get_file_content(char *path, t_cub3d *data);
int     store_textures_path(t_cub3d *data, int length);
int     is_map_line(char *line);
int     empty_line(char *line);
int     check_if_map_line(char *line);
void    parse_file_content(t_cub3d *data);
int     store_map(t_cub3d *data, int index);

int     check_path_rgb(t_cub3d *data);
void    check_map(t_cub3d *data);
void    init_game(char *path_file, t_cub3d *data);


char    	*return_rgb_string(char *line);
long    	rgb_to_hex(char *line);
uint32_t    get_texel(mlx_image_t *img, int x, int y);


void    duplicate_player(t_cub3d *data);
void    get_player_pos(t_cub3d *data);
void    check_dimensions(t_cub3d *data);
void    check_walls(t_cub3d *data);
void    check_valid_path(t_cub3d *data);

#endif