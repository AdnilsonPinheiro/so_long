/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:44:33 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/11 16:03:36 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static unsigned int	g_seed;
/// @brief Fills map in order to find if exit is reacheble
/// @param matrix the map
/// @param y vertical axis
/// @param x horizontal axis
void	ft_fillexit(char **matrix, int y, int x)
{
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	if (ft_strchr("F1", matrix[y][x]) || matrix[y][x] == '\0')
		return ;
	else if (y < 0 || x < 0 || x > (int)ft_strlen(matrix[y]) || y >= i)
		return ;
	matrix[y][x] = 'F';
	ft_fillexit(matrix, y + 1, x);
	ft_fillexit(matrix, y, x + 1);
	ft_fillexit(matrix, y - 1, x);
	ft_fillexit(matrix, y, x - 1);
}
/// @brief check if exit was reached from player's starting position
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
/// @brief creates a pseudo-random number to assign the sushi
int	lcg_rand(void)
{
	g_seed = (1103515245 * g_seed + 12345) & 0x7fffffff;
	return (g_seed);
}
/// @brief assigns a different sushi image based on lcg_rand and the collectable's coordinates
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
