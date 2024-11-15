/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:40:36 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 04:59:36 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define TILE_SIZE 30
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define FOV_DEGREES 60
# define COLOR_FLOOR 0xB994702F
# define COLOR_CEILING 0x89CFF32F
# define COLOR_WALL_N 0xF5F5F2FF
# define COLOR_WALL_S 0xF5F5F2FF
# define COLOR_WALL_E 0xB5B5B2FF
# define COLOR_WALL_W 0xB5B5B2FF

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	double	x;
	double	y;
	double	heading;
	float	fov_radians;
}	t_player;

typedef struct s_map_data
{
	char	**info;
	char	**copy;
	int		rows;
	int		map_rows;
	char	*floor_color;
	char	*ceiling_color;
	char	*n_wall_asset;
	char	*s_wall_asset;
	char	*e_wall_asset;
	char	*w_wall_asset;
	char	**map;

}	t_map_data;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*so;
}	t_texture;

typedef struct s_ray
{
	int		h_hit;
	float	angle_rad;
	double	distance;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map_data	map;
	int			p_x;
	int			p_y;
	int			w_map;
	int			h_map;
	t_player	player;
	t_texture	textures;
	mlx_image_t	*image;
}	t_game;

t_vector	vec_new(double x, double y);
t_vector	vec_zero(void);
t_vector	vec_from_angle(float angle);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul(t_vector v, double n);
double		vec_len(t_vector v);
t_vector	vec_normalize(t_vector v);
double		vec_dot_product(t_vector v1, t_vector v2);
t_vector	vec_inverse(t_vector v);
int			vec_equal(t_vector v1, t_vector v2);
double		vec_angle(t_vector v);
t_vector	vec_rotate(t_vector v, int angle);
void		vec_print(t_vector v);
void		start_game(t_game *game);
void		init_game(t_game *game);
void init_player(t_game *game);
void raycasting(t_game *game);
void draw_column(t_game *game, t_ray *ray, int col);
float angle_norm(float angle);
int load_textures(t_game *game);
void calculate_ray_distance(t_game *game);
void calculate_ray_data(t_game *game, double ray_offset);
void set_vertical_texture(t_game *game);
void set_horizontal_texture(t_game *game);
void zoom_in(t_game *game);
void zoom_out(t_game *game);
uint32_t get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y);
void set_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
uint32_t rgba(int r, int g, int b, int a);
uint32_t hex_to_int(const char *hex);
void mlx_key(mlx_key_data_t keydata, void *param);
void game_exit(t_game *game);
void start_game(t_game *game);
void game_loop(void *param);
void init_player(t_game *game);
void check_textures(t_game *game);

#endif