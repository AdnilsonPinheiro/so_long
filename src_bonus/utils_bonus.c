/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:44:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 20:57:35 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static unsigned int	g_seed;

void	ft_fillexit(char **matrix, int y, int x)
{
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	if (ft_strchr("FX1", matrix[y][x]) || matrix[y][x] == '\0')
		return ;
	else if (y < 0 || x < 0 || x > (int)ft_strlen(matrix[y]) || y >= i)
		return ;
	matrix[y][x] = 'F';
	ft_fillexit(matrix, y + 1, x);
	ft_fillexit(matrix, y, x + 1);
	ft_fillexit(matrix, y - 1, x);
	ft_fillexit(matrix, y, x - 1);
}

void	ft_checkexit(char **matrix, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (matrix[i][j] == 'E')
			{
				ft_freematrix(matrix, NULL);
				ft_cleanmap("Exit out of reach\n", map, FLOOD_ER);
			}
		}
	}
}

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

void	ft_rand_enemy(t_game *game, int x, int y)
{
	int	rand_index;

	if (!game)
		return ;
	g_seed = x * 1000 + y * 100 + 12345;
	rand_index = lcg_rand() % ENEMY_COUNT;
	mlx_put_image_to_window(game->mlx, game->win, 
		game->enemy[rand_index]->img, x * TITLE, y * TITLE);
}