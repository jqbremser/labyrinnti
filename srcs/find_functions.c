/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:11:15 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/24 17:23:10 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		find_map(t_map_data	*game);
int			find_player(t_map_data	*game, int x, int y, int P_found);
static int	find_asset(t_map_data	*game);
static int	find_no_map(t_map_data *game);
static void	find_ones(t_map_data *game, int x, int y, int a);
static int title_check(t_map_data *game, char *line);


/* Finds and stores the assets related to walls, floor, and ceiling in
   the `game` structure. Calls `handle_error` if no valid map is found. */
void	find_map(t_map_data	*game)
{
	if (find_no_map(game))
		handle_error(EXIT_NO_MAP, game);
	if (find_asset(game))
		handle_error(EXIT_NO_ASSETS, game);
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

static int find_asset(t_map_data	*game)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (game->info[y][x])
	{
		printf("before title check\n");
		if (!title_check(game, game->info[y]))
			y++;
		
	}
	return (0);
}

static int title_check(t_map_data *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		printf("NO:here\n");
		if (!game->n_wall_asset)
		{
			printf("SO:1\n");
			game->n_wall_asset = ft_strdup(line + 3);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		printf("SO:here\n");
		if (!game->s_wall_asset)
		{
			printf("SO:1\n");
			game->s_wall_asset = ft_strdup(line + 3);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		printf("WE:here\n");
		if (!game->w_wall_asset)
		{
			printf("WE:1\n");
			game->w_wall_asset = ft_strdup(line + 3);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		printf("EA:here\n");
		if (!game->e_wall_asset)
		{
			printf("EA:1\n");
			game->e_wall_asset = ft_strdup(line + 3);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		printf("F:here\n");
		if (!game->floor_color)
		{
			printf("F:1\n");
			game->floor_color= ft_strdup(line + 2);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		printf("C:here\n");
		if (!game->ceiling_color)
		{
			printf("C:1\n");
			game->ceiling_color= ft_strdup(line + 3);
		}
		else
		{
			printf("else\n");
			handle_error(EXIT_NO_ASSETS, game);	
		}
	}
	return (0);

		
}

/* Searches for an asset in the `game` structure by matching `arg` with
   the starting part of each entry in `game->info`. Returns the asset as
   a new string, or NULL if not found. */
// static int find_asset(t_map_data	*game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	x = 0;
// 	while (game->info[y])
// 	{
// 		while (game->info[y][x])
// 		{
// 			if (!ft_strncmp(&game->info[y][x], "NO ", 3))
// 			{
// 				x = 3;
// 				// while (!ft_strncmp(&game->info[y][x], " ", 1))
// 				// 	x++;
// 				game->n_wall_asset = (ft_strdup(&game->info[y][x]));
// 				printf("n_wall:%s\n", game->n_wall_asset);
// 				y++;
// 			}
// 			else if (!ft_strncmp(&game->info[y][x], "SO ", 3))
// 			{
// 				x = 2;
// 				while (!ft_strncmp(&game->info[y][x], " ", 1))
// 					x++;
// 				game->s_wall_asset = (ft_strdup(&game->info[y][x]));
// 				y++
// 			}
// 			else if (!ft_strncmp(&game->info[y][x], "WE ", 3))
// 			{
// 				x = 2;
// 				while (!ft_strncmp(&game->info[y][x], " ", 1))
// 					x++;
// 				game->w_wall_asset = (ft_strdup(&game->info[y][x]));
// 				y++;
// 			}
// 			else if (!ft_strncmp(&game->info[y][x], "EA ", 3))
// 			{
// 				x = 2;
// 				while (!ft_strncmp(&game->info[y][x], " ", 1))
// 					x++;
// 				game->e_wall_asset = (ft_strdup(&game->info[y][x]));
// 				y++;
// 			}
// 			else if (!ft_strncmp(&game->info[y][x], "F ", 2))
// 			{
// 				x = 1;
// 				while (!ft_strncmp(&game->info[y][x], " ", 1))
// 					x++;
// 				game->floor_color = (ft_strdup(&game->info[y][x]));
// 				y++;
// 			}
// 			else if (!ft_strncmp(&game->info[y][x], "C ", 2))
// 			{
// 				x = 1;
// 				while (!ft_strncmp(&game->info[y][x], " ", 1))
// 					x++;
// 				game->ceiling_color = (ft_strdup(&game->info[y][x]));
// 				y++;
// 			}
// 			if (game->info[y][x] == ' ' || game->info[y][x] == '\t' || game->info[y][x] == '\n'))
// 				x++;
// 			else
// 			{
// 				printf("here\n");
// 				return(1);
// 			}
// 		}
// 		y++;
// 	}
// 	return (0);
// }


// 		/*  ft_strncmp all of these:
		
// 		 	game->n_wall_asset = find_asset(game, "NO ");
// 	game->s_wall_asset = find_asset(game, "SO ");
// 	game->w_wall_asset = find_asset(game, "WE ");
// 	game->e_wall_asset = find_asset(game, "EA ");
// 	game->floor_color = find_asset(game, "F ");
// 	game->ceiling_color = find_asset(game, "C ");*/



// 		if (!ft_strncmp(&game->info[y][x], "NO ", 3)
// 		{
// 			x = 2;
// 			while (!ft_strncmp(&game->info[y][x], " ", 1))
// 				x++;
// 			game->n_wall_asset = (ft_strdup(&game->info[y][x]));
// 		}
// 			// || !ft_strncmp(&game->info[y][x], "SO ", 3)
// 			// || !ft_strncmp(&game->info[y][x], "EA ", 3)
// 			// || !ft_strncmp(&game->info[y][x], "WE ", 3))
// 		y++;
// 	}
// 	return (NULL);
// }

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
