/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:17:14 by hlee-sun          #+#    #+#             */
/*   Updated: 2025/01/24 14:26:28 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int			init_game(t_map_data *game);
void		set_heading(t_map_data	*game, int y, int x);
static int	trim_lb_and_check(char *str);
static int	load_textures(t_map_data *game);
static int	parse_color(char *color_in, uint32_t *color_out);

/* Initializes the game state with default values, including setting up
   the player's starting position, the camera's field of view, and the 
   focal length. It also loads the textures and parses the floor and 
   ceiling colors. */
int	init_game(t_map_data *game)
{
	game->player.x = game->player.x * TILE_SIZE + TILE_SIZE / 2;
	game->player.y = game->player.y * TILE_SIZE + TILE_SIZE / 2;
	game->player.rotating = MOVE_STOP;
	game->player.moving_ahead = MOVE_STOP;
	game->player.moving_side = MOVE_STOP;
	game->mlx = NULL;
	game->image = NULL;
	game->camera.fov_radians = (FOV_DEGREES * M_PI) / 180;
	game->camera.focal_length = (SCREEN_WIDTH / 2)
		/ tan(game->camera.fov_radians / 2);
	game->camera.angle_increment = game->camera.fov_radians / SCREEN_WIDTH;
	if (load_textures(game) == 0)
		return (EXIT_TEXTURE_LOAD_FAIL);
	if (parse_color(game->floor_color, &(game->textures.floor)) == 0
		|| parse_color(game->ceiling_color, &(game->textures.ceiling)) == 0)
		return (EXIT_PARSE_COLOR_FAIL);
	return (1);
}

/* Sets the player's initial heading based on the map symbol at the 
   specified coordinates. 'N', 'E', 'S', and 'W' correspond to different 
   heading values (angles). */
void	set_heading(t_map_data	*game, int y, int x)
{
	if (game->map[y][x] == 'N')
		game->player.heading = 3 * M_PI / 2;
	if (game->map[y][x] == 'E')
		game->player.heading = 0;
	if (game->map[y][x] == 'S')
		game->player.heading = M_PI / 2;
	if (game->map[y][x] == 'W')
		game->player.heading = M_PI;
}

/* Trims the last character (newline) from a string. */
static int	trim_lb_and_check(char *str)
{
	int	fd;

	str[ft_strlen(str) - 1] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	close (fd);
	return (1);
}

/* Loads the textures for the walls (north, south, east, west) from the
   asset file paths provided in the game struct. If any texture fails to
   load, it returns 0 (failure). */
static int	load_textures(t_map_data *game)
{
	if (trim_lb_and_check(game->n_wall_asset) == 1)
		game->textures.n = mlx_load_png(game->n_wall_asset);
	if (trim_lb_and_check(game->s_wall_asset) == 1)
		game->textures.s = mlx_load_png(game->s_wall_asset);
	if (trim_lb_and_check(game->e_wall_asset) == 1)
		game->textures.e = mlx_load_png(game->e_wall_asset);
	if (trim_lb_and_check(game->w_wall_asset) == 1)
		game->textures.w = mlx_load_png(game->w_wall_asset);
	if (!game->textures.w || !game->textures.n
		|| !game->textures.s || !game->textures.e)
	{
		mlx_clean(game);
		return (0);
	}
	return (1);
}

/* Parses a color in the format "R,G,B" (where R, G, B are integers) and
   converts it into a uint32_t color value. It returns 1 on success, 
   or 0 if parsing fails. */
static int	parse_color(char *color_in, uint32_t *color_out)
{
	char	**colors_str;
	int		*colors_int;
	int		i;

	colors_str = ft_split(color_in, ',');
	if (!colors_str)
		return (0);
	colors_int = malloc(3 * sizeof(int));
	if (!colors_int)
	{
		free(colors_str);
		return (0);
	}
	i = -1;
	while (++i < 3 && colors_str[i])
		colors_int[i] = ft_atoi(colors_str[i]);
	free_array(colors_str);
	if (i < 3)
	{
		free(colors_int);
		return (0);
	}
	*color_out = rgba(colors_int[0], colors_int[1], colors_int[2], 255);
	free(colors_int);
	return (1);
}
