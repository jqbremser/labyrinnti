/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:22:39 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/11/15 01:22:44 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int main(void)
{
	t_game	game;

	init_game(&game);
	start_game(&game);
	return 0;
}