/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:04:58 by jbremser          #+#    #+#             */
/*   Updated: 2025/01/14 17:45:18 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void map_background(t_map_data *game)
{
	int i;
	int j;
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (j < game->map_cols)
		{
			mlx_put_pixel(game->minimap, j, i, get_rgba(1, 1, 1, 1));
			j++;
		}
		i++;
	}
}

void	init_minimap(t_map_data *game, t_minimap *mm)
{
	mm->x = 0;
	mm->y = 0;
	mm->i = 0;
	mm->k = 0;
	mm->px_x = 0;
	mm->px_y = 0;
	map_background(game);
}


void	draw_mm_open_space(t_map_data *game, t_minimap *mm)
{
	while (mm->k < game->mm)
	{
		while (mm->i < game->mm)
		{
			mlx_put_pixel(game->minimap, mm->px_x + mm->i, mm->px_y + mm->k, get_rgba(0, 0 , 0, 255));
			mm->i++;
		}
		mm->i = 0;
		mm->k++;
	}
	mm->k = 0;

}
void	draw_mm_wall(t_map_data *game, t_minimap *mm)
{
	while (mm->k < game->mm)
	{
		while (mm->i < game->mm)
		{
			mlx_put_pixel(game->minimap, mm->px_x + mm->i, mm->px_y + mm->k, get_rgba(200, 200 , 200, 255));
			mm->i++;
		}
		mm->i = 0;
		mm->k++;
	}
	mm->k = 0;

}


void	draw_squares(t_map_data *game)
{
	t_minimap	mm;

	init_minimap(game, &mm);
	while (game->map[mm.y])
	{
		while (game->map[mm.y][mm.x] != '\0')
		{
			if (game->map[mm.y][mm.x] == '0'
				|| ft_strchr("NESW", game->map[mm.y][mm.x]))
				draw_mm_open_space(game, &mm);
			else if (game->map[mm.y][mm.x] == '1')
				draw_mm_wall(game, &mm);
			mm.x++;
			mm.px_x += game->mm;
		}
		mm.px_y += game->mm;
		mm.px_x = 0;
		mm.x = 0;
		mm.y++;
	}
}



void draw_minimap(mlx_t *mlx, t_map_data *game)
{
	mlx_image_to_window(game->mlx, game->minimap, 20, 20);
	game->x_len = 0;
	game->y_len = 0;
	game->x_len = ft_strlen(game->map[0]);
	while (game->map[game->y_len])
		game->y_len++;
	draw_squares(game);
	(void)mlx;
	// mlx_image_to_window(mlx, game->plyr, 20, 20);

	// mlx_image_to_window(mlx)
}