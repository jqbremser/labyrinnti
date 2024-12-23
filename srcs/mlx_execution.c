/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:19:41 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/12/19 14:19:49 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void game_loop(void *param)
{
    t_map_data *game = param;

	if (game->image != NULL)
    	mlx_delete_image(game->mlx, game->image);
    game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->image) 
	{
        printf("Failed to create new image\n");
		// TODO add freeing of memory before exit
        exit(1);
    }
    raycasting(game);
    mlx_image_to_window(game->mlx, game->image, 0, 0);
}

void start_game(t_map_data *game)
{
    game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", 0);
	if (!game->mlx) 
	{
		printf("Failed to initialize mlx\n");
		exit(1);
    }
	printf("\nafter mlx_init\n");
    mlx_loop_hook(game->mlx, &game_loop, game);
	printf("\nafter mlx_loop_hook\n");
    mlx_key_hook(game->mlx, &mlx_key, game);
	printf("\nafter mlx_key_hook\n");
    if (game->mlx == NULL)
       	printf("\nmlx is NULL\n");
    else
       	printf("\n mlx isnt NULL?!?!?!\n");
    mlx_loop(game->mlx);
    printf("\nafter loop\n");
}


void game_exit(t_map_data *game)
{
    if (game->image != NULL) 
	{
        mlx_delete_image(game->mlx, game->image);
    }
    if (game->mlx != NULL) 
	{
        mlx_terminate(game->mlx);
    }
    exit(0);
}

// void move_player(t_map_data *game, char *direction)
// {
//     if (strcmp(direction, "UP"))
        
// }

void mlx_key(mlx_key_data_t keydata, void *param)
{
    t_map_data *game;

    game = param;
    if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
        game_exit(game);
    // if ((keydata.key == MLX_KEY_UP || MLX_KEY_W) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) 
    // {  
    //     move_player(game, "UP");

    // }
    //add movement here!
}

