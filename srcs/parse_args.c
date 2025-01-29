/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:33:12 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/29 16:30:16 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int			parse_args(char **argv, t_map_data	*game);
static int	map_parse(char **argv, t_map_data	*game);
static void	map_to_str(t_map_data *game, char *argv);
static int	map_rows(char *arg);

/* Parses the command-line arguments provided to the program. It checks
   the validity of the map file name (should end with `.cub`), parses the
   map, ensures exactly one player is found, and performs a minesweep on
   the map. Returns appropriate error codes for various failures, or
   1 on success. */
int	parse_args(char **argv, t_map_data	*game)
{
	(void)game;
	if (!argv)
		return (EXIT_ARG_COUNT_ERROR);
	if ((ft_strlen(argv[1]) <= 4) || (argv[1][ft_strlen(argv[1]) - 5] == '/')
		|| (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0))
		return (EXIT_ARG_NAME_ERROR);
	if (map_parse(argv, game))
		return (EXIT_MAP_INIT_ERROR);
	if (find_player(game, game->temp_x, game->temp_y, game->temp_a) != 1)
		return (EXIT_NO_PLAYER);
	if (minesweep(game))
		return (EXIT_MINESWEEP_ERROR);
	else
		return (1);
}

/* When complete, there will be an game->map char** that contains the entire map
	All data from map.cub came in as part of game->info, and then this is
	cleaned out with all of the info saved in game struct */
static int	map_parse(char **argv, t_map_data	*game)
{
	game->rows = map_rows(argv[1]);
	if (game->rows == -1)
	{
		game->rows = 0;
		return (1);
	}
	map_to_str(game, argv[1]);
	// int x = 0;
	// while (game->info[x])
	// 	printf("%s", game->info[x++]);
	// check_info(game, game->info);
	find_map(game);
	return (0);
}


/* Turns the map.cub file into a char** and saves it in game->info */
static void	map_to_str(t_map_data *game, char *argv)
{
	int			fd;
	int			i;

	fd = 0;
	i = 0;
	game->info = (char **)ft_calloc((size_t)game->rows + 1, sizeof(char *));
	if (!game->info)
		handle_error(EXIT_MAP_INIT_CALLOC_FAIL, game);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		handle_error(EXIT_FD_OPEN_ERROR, game);
	while (game->rows > i)
	{
		game->info[i] = get_next_line(fd);
		i++;
	}
	close (fd);
}

/* uses GNL to find the amount of rows*/
static int	map_rows(char *arg)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	line = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free (line);
	close (fd);
	return (i);
}
