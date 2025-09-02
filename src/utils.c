/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:44:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/02 19:55:43 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static unsigned int	seed;

int	lcg_rand(void)
{
	seed = (1103515245 * seed + 12345) & 0x7fffffff;
	return seed;
}

void	ft_rand_collect(t_game *game, int x, int y)
{
	if (!game)
		return ;
	seed = x * 1000 + y * 100 + 12345;
	int rand_index = lcg_rand() % COLLECT_COUNT;
	mlx_put_image_to_window(game->mlx, game->win, game->collect[rand_index]->img, x * TITLE, y * TITLE);
}
