/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/29 17:05:17 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		find_map(t_map_data	*game);
int			find_player(t_map_data	*game, int x, int y, int P_found);
static char	*find_asset(t_map_data	*game, char	*arg);
static int	find_no_map(t_map_data *game);
static void	find_ones(t_map_data *game, int x, int y, int a);






static bool check_map(char **info, int y)
{	
	int x;
	int p_found;

	p_found = 0;
	x = 0;
	while (info[y][x] != '\0')
    {
        // Valid map characters: '1', '0', ' ' (space)
        if (info[y][x] == '1' || info[y][x] == '0' || info[y][x] == ' ')
		{
            x++;
        }
        // Valid player characters: N, S, W, E
        else if (ft_strchr("NSWE", info[y][x]))
		{
            p_found++;
            if (p_found > 1) {
                // More than one player character found in the map
                printf("Error: Found too many players in the map at line %d\n", y);
                return false;
            }
            x++;
        }
		else
		{
            // Invalid character found in the map
            printf("Error: Found invalid character in the map at line %d\n", y + 1);
            return false;
        }
    }
    return true;
}

static int check_info(t_map_data *game)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (game->info[y])
	{
		if (!ft_strcmp(game->info[y], "\n"))
		{
			if (!ft_strncmp(game->info[y], "NO ", 3)
			|| !ft_strncmp(game->info[y], "SO ", 3)
			|| !ft_strncmp(game->info[y], "EA ", 3)
			|| !ft_strncmp(game->info[y], "WE ", 3)
			|| !ft_strncmp(game->info[y], "F ", 2)
			|| !ft_strncmp(game->info[y], "C ", 2))
			// || !check_map(game->info, y)) //check the line for map marks
				return (1);
		}
		printf("%s", game->info[y]);
		if (!check_map(game->info, y))
			return (1);
		y++;
	}
	return (0);
}

/* Finds and stores the assets related to walls, floor, and ceiling in
   the `game` structure. Calls `handle_error` if no valid map is found. */
void	find_map(t_map_data	*game)
{
	if (find_no_map(game))
		handle_error(EXIT_NO_MAP, game);
	if (check_info(game))
		handle_error(EXIT_NO_MAP, game);
	game->n_wall_asset = find_asset(game, "NO ");
	game->s_wall_asset = find_asset(game, "SO ");
	game->w_wall_asset = find_asset(game, "WE ");
	game->e_wall_asset = find_asset(game, "EA ");
	game->floor_color = find_asset(game, "F ");
	game->ceiling_color = find_asset(game, "C ");
	if (game->n_wall_asset == NULL || game->s_wall_asset == NULL
		|| game->w_wall_asset == NULL || game->e_wall_asset == NULL
		|| game->floor_color == NULL || game->ceiling_color == NULL)
		handle_error(EXIT_NO_ASSETS, game);
	if (check_color(game->floor_color) || check_color(game->ceiling_color))
		handle_error(EXIT_PARSE_COLOR_FAIL, game);
	find_ones(game, game->temp_x, game->temp_y, game->temp_a);
	if (find_extras(game->map))
		handle_error(EXIT_EXTRA_ABC, game);
}

/* Searches the map for a player character ('N', 'S', 'W', 'E'), sets the
   player's position, and returns the count of found players. */
int	find_player(t_map_data	*game, int x, int y, int P_found)
{
	P_found = 0;
	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (ft_strchr("NSWE", game->map[y][x]))
			{
				set_heading(game, y, x);
				game->player.y = y;
				game->player.x = x;
				game->map[y][x] = '0';
				P_found++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (P_found);
}

/* Searches for an asset in the `game` structure by matching `arg` with
   the starting part of each entry in `game->info`. Returns the asset as
   a new string, or NULL if not found. */
static char	*find_asset(t_map_data	*game, char	*arg)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->info[y])
	{
		if (!ft_strncmp(&game->info[y][x], arg, ft_strlen(arg)))
		{
			x = ft_strlen(arg) - 1;
			while (!ft_strncmp(&game->info[y][x], " ", 1))
				x++;
			return (ft_strdup(&game->info[y][x]));
		}
		y++;
	}
	return (NULL);
}

/* Checks if there is a valid map in the `game` structure by scanning
   for the first occurrence of a '1' in `game->info`. Returns 1 if no
   valid map is found, otherwise returns 0. */
static int	find_no_map(t_map_data *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (game->info[y])
	{
		x = 0;
		while (game->info[y][x] == ' ')
			x++;
		if (game->info[y][x] == '1')
			return (0);
		y++;
	}
	return (1);
}

/* Creates a map by copying the relevant portion of `game->info` starting
   from the first '1' character. The map is stored in `game->map`. If
   memory allocation fails, an error is handled. */
static void	find_ones(t_map_data *game, int x, int y, int a)
{
	y = 0;
	x = 0;
	a = 0;
	while (y < game->rows && game->info[y])
	{
		x = 0;
		while (game->info[y][x] && game->info[y][x] == ' ')
			x++;
		game->map_rows = game->rows - y + 1;
		if (game->info[y][x] && game->info[y][x] == '1')
		{
			game->map = ft_calloc((game->rows - y + 1), sizeof(char *));
			if (!game->map)
				handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);
			while (game->info[y])
			{
				game->map[a] = ft_strdup(game->info[y]);
				a++;
				y++;
			}
		}
		y++;
	}
}
