/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:44:21 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/14 17:35:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 1800
# define SCREEN_HEIGHT 1600
# define TILE_SIZE 30
# define FOV_DEGREES 60
# define ROTATION_SPEED 0.02
# define PLAYER_SPEED 1.5

typedef enum s_error_code
{
	EXIT_ARG_COUNT_ERROR = 200,
	EXIT_INVALID_ARGS = 201,
	EXIT_ARG_NAME_ERROR = 202,
	EXIT_MAP_INIT_ERROR = 203,
	EXIT_MAP_INIT_CALLOC_FAIL = 204,
	EXIT_FD_OPEN_ERROR = 205,
	EXIT_NO_MAP = 206, 
	EXIT_TEXTURE_LOAD_FAIL = 207,
	EXIT_PLAYER_SEARCH_FAIL = 208,
	EXIT_PARSE_COLOR_FAIL = 209,
	EXIT_MINESWEEP_ERROR = 210,
	EXIT_NO_PLAYER = 211,
}	t_error;

typedef enum s_movement_direction
{
	MOVE_STOP = 0,
	MOVE_FORWARD = 1,
	MOVE_BACK = 2,
	MOVE_LEFT = 3,
	MOVE_RIGHT = 4,
	ROT_LEFT = 5,
	ROT_RIGHT = 6
}	t_movement_direction;

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
	int		rotating;
	int		moving_ahead;
	int		moving_side;
}	t_player;

typedef struct s_keys
{
	int	move_forward;
	int move_back;
	int move_left;
	int move_right;
	int rotate_left;
	int rotate_right;
}	t_keys;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
	uint32_t		floor;
	uint32_t		ceiling;
}	t_texture;


typedef struct s_camera
{
	double	fov_radians;
	double	focal_length;
	double	angle_increment;
}	t_camera;

typedef struct s_ray
{
	int			h_hit;
	float		angle_rad;
	double		distance;
	double		wall_h;
	double 		hit_part;
	uint32_t	x;
}	t_ray;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	px_x;
	int	px_y;
	int	i;
	int	k;

	// // t_map_data	game;
	// char		*wall_asset;
	// char		*floor_asset;
	// char		*player_asset;
	// char 		*sightline;
	// t_player	*player;
}	t_minimap;

typedef struct s_map_data
{
	char    **info;
	int		rows;
	int		map_rows;
	int		map_cols;
	char	*floor_color;
	char	*ceiling_color;
	char	*n_wall_asset;
	char	*s_wall_asset;
	char	*e_wall_asset;
	char	*w_wall_asset;
	char	**map;
	char	**copy;
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*minimap;
	t_player	player;
	t_player	temp_player;
	t_keys		keys_pressed;
	t_texture	textures;
	t_camera	camera;
	int			mm;
	int			x_len;
	int			y_len;
	// t_minimap	minimap;
}   t_map_data;



/* ************************************************************************** */
/*									error_handling							  */
/* ************************************************************************** */
int			handle_error(int errno, t_map_data *game);
void		clean_info_struct(t_map_data *game);
void		free_game_struct(t_map_data	*game);
void		free_array(char **str);


/* ************************************************************************** */
/*									parse_args								  */
/* ************************************************************************** */
int			parse_args(char **argv, t_map_data	*game);
void		print_map(char **map);

/* ************************************************************************** */
/*									find_functions							  */
/* ************************************************************************** */
int			find_player(t_map_data	*game);
void		find_map(t_map_data	*game);

/* ************************************************************************** */
/*									utils									  */
/* ************************************************************************** */
int			init_game(t_map_data *game);
void		print_info(t_map_data *game);
void		print_map(char **map);

/* ************************************************************************** */
/*									minesweep								  */
/* ************************************************************************** */
int minesweep(t_map_data *game);


/* ************************************************************************** */
/*									raycasting								  */
/* ************************************************************************** */
t_vector	vec_new(double x, double y);
t_vector	vec_from_angle(float angle);
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mul(t_vector v, double n);
double		vec_len(t_vector v);
void		start_game(t_map_data *game);
void 		raycasting(t_map_data *game);
void 		draw_column(t_map_data *game, t_ray *ray);
float		angle_norm(float angle);
uint32_t	get_tex_color(mlx_texture_t *tex, uint32_t x, uint32_t y);
void		set_image_color(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
uint32_t	rgba(int r, int g, int b, int a);
void		mlx_key(mlx_key_data_t keydata, void *param);
void		game_exit(t_map_data *game);
void		start_game(t_map_data *game);
void		game_loop(void *param);
void		player_loop(void *param);
void		handle_movement_pressed(mlx_key_data_t keydata, t_map_data *game);
void		handle_movement_released(mlx_key_data_t keydata, t_map_data *game);

void		draw_minimap(mlx_t *mlx, t_map_data *game);


#endif