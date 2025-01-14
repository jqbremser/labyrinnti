/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:00:30 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/14 16:41:01 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_array(char **str);
int		handle_error(int errno, t_map_data *game);
void 	free_string(char *str);
void	free_game_struct(t_map_data	*game);
void	map_free_error(int errno, t_map_data *game);


void	free_array(char **str)
{
	int	y;

	y = 0;
	while (str[y])
	{
		// printf("to be freed: %s\n", str[y]);
		free(str[y++]);
	}
	free(str);
}


void free_string(char *str)
{
	// printf("to be freed: %s\n", str);
    if (str)
        free(str);
}

void	free_game_struct(t_map_data	*game)
{
	// if (game->copy)
	// 	free_array(game->copy);
	// if (game->info)
	// 	free_array(game->info);
	if (game->map)
	{
		// printf("\nmap exists\n");
		free_array(game->map);	
	}
	free_string(game->n_wall_asset);
	free_string(game->s_wall_asset);
	free_string(game->e_wall_asset);
	free_string(game->w_wall_asset);
	free_string(game->ceiling_color);	
	free_string(game->floor_color);
	if (game)
		free(game);
}

void	map_free_error(int errno, t_map_data	*game)
{
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		printf("Error: Calloc fail\n");
	if (errno == EXIT_FD_OPEN_ERROR)
		printf("FD NO OPEN!\n");
	if (errno == EXIT_NO_MAP)
		printf("WHERE MAP!\n");
	if (errno == EXIT_TEXTURE_LOAD_FAIL)
		printf("Texture loading failed\n");
	if (errno == EXIT_PLAYER_SEARCH_FAIL)
		printf("Failed to find player on map\n");
	if (errno == EXIT_PARSE_COLOR_FAIL)
		printf("Failed to parse floor or ceiling color\n");
	if (errno == EXIT_MINESWEEP_ERROR)
		printf("Minesweep failed: open area on map\n");
	if (errno == EXIT_NO_PLAYER)
		printf("Invalid amount of Player(s) found on map\n");
	// if (errno == EXIT_MULT_PLAYERS)
	// 	printf("Multiples Players found on map\n");
	if (game)
		free_game_struct(game);
	exit(2);
}

int	handle_error(int errno, t_map_data *game)
{
	if (errno == EXIT_ARG_COUNT_ERROR)
   		write(2, "Invalid amount of Args\n", 24);
	if (errno == EXIT_INVALID_ARGS)
   		write(2, "Invalid Arguments\n", 19);
	if (errno == EXIT_ARG_NAME_ERROR)
   		write(2, "Invalid File Names\n", 20);
	if (errno == EXIT_MAP_INIT_CALLOC_FAIL)
		map_free_error(errno, game);
	if (errno == EXIT_FD_OPEN_ERROR)
		map_free_error(errno, game);
	if (errno == EXIT_MAP_INIT_ERROR)
		map_free_error(errno, game);	
	if (errno == EXIT_NO_MAP)
		map_free_error(errno, game);
	if (errno == EXIT_TEXTURE_LOAD_FAIL)
		map_free_error(errno, game);
	if (errno == EXIT_PLAYER_SEARCH_FAIL)
		map_free_error(errno, game);
	if (errno == EXIT_PARSE_COLOR_FAIL)
		map_free_error(errno, game);
	if (errno == EXIT_MINESWEEP_ERROR)
		map_free_error(errno, game);
	if (errno == EXIT_NO_PLAYER)
		map_free_error(errno, game);
	if (errno == 0)
		return (0);
	else
		return (1);	
}

// void clean_info_struct(t_map_data	*game)
// {
// 	// if (game->copy)
// 	// 	free_array(game->copy);
// 	if (game->info)
// 		free_array(game->info);
// }