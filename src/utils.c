/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:44:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 14:32:16 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static unsigned int	g_seed;

int	lcg_rand(void)
{
	g_seed = (1103515245 * g_seed + 12345) & 0x7fffffff;
	return (g_seed);
}

void	ft_rand_collect(t_game *game, int x, int y)
{
	int	rand_index;

	if (!game)
		return ;
	g_seed = x * 1000 + y * 100 + 12345;
	rand_index = lcg_rand() % COLLECT_COUNT;
	mlx_put_image_to_window(game->mlx, game->win,
		game->collect[rand_index]->img, x * TITLE, y * TITLE);
}
