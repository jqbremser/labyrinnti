/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:33:12 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/14 16:42:05 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int			parse_args(char **argv, t_map_data	*game);
static int	map_parse(char **argv, t_map_data	*game);
static void	map_to_str(t_map_data *game, char *argv);
static int	map_rows(char *arg);




int	parse_args(char **argv, t_map_data	*game)
{
	(void)game;
	if (!argv)
		return (EXIT_ARG_COUNT_ERROR);
	if ((ft_strlen(argv[1]) <= 4) || (argv[1][ft_strlen(argv[1]) - 5] == '/')
		|| (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0))
		return (EXIT_ARG_NAME_ERROR);
	if (map_parse(argv, game))
	{
		printf("no assets\n");
		return (EXIT_MAP_INIT_ERROR);
	}
	if (find_player(game) != 1)
		return (EXIT_NO_PLAYER);
	// if (find_player(game) > 1)
	// 	return (EXIT_MULT_PLAYERS);
	if (minesweep(game))
		return (EXIT_MINESWEEP_ERROR);
	else
	{
		printf("\nNICE FILE!\n");
		return (1);
	}
}

/* When complete, there will be an game->map char** that contains the entire map. All data from map.cub came
	in as part of game->info, and then this is cleaned out with all of the info saved in game struct */
static int	map_parse(char **argv, t_map_data	*game)
{
	// printf("\nbefore maprows\n");
	game->rows = map_rows(argv[1]);
   	// printf("\nafter maprows\n");
    if (game->rows == -1)
    {
		printf("\ninside here\n");
	    game->rows = 0;
        return (1);
    }
	map_to_str(game, argv[1]);
	find_map(game);

	if (game->info)
		free_array(game->info);
	printf("after clean_info_struct\n");
	if (game->n_wall_asset == NULL || game->s_wall_asset == NULL ||
			game->w_wall_asset == NULL || game->e_wall_asset == NULL ||
				game->ceiling_color == NULL || game->floor_color == NULL)
	{
		printf("\nassets incorrectly loaded\n");
		return (1);
	}
    return (0);
}

/* Turns the map.cub file into a char** and saves it in game->info */
static void map_to_str(t_map_data *game, char *argv)
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