/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floodfill_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:29:31 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 19:10:56 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	**ft_matrixdup(t_map *map);
static void	ft_fill(char **matrix, int y, int x);
static void	ft_checkfill(char **matrix, t_map *map);

void	ft_floodfill(t_map *map, int y, int x)
{
	char	**matrix;

	matrix = ft_matrixdup(map);
	ft_fill(matrix, y, x);
	ft_checkfill(matrix, map);
	ft_freematrix(matrix, NULL);
	matrix = ft_matrixdup(map);
	ft_fillexit(matrix, y, x);
	ft_checkexit(matrix, map);
	ft_freematrix(matrix, NULL);
}

static char	**ft_matrixdup(t_map *map)
{
	char	**matrix;
	int		i;
	int		j;

	matrix = malloc(sizeof(char *) * (map->size + 1));
	if (!matrix)
		ft_cleanmap("Failed to floodfill\n", map, FLOOD_ER);
	i = -1;
	while (map->matrix[++i])
	{
		matrix[i] = malloc(sizeof(char *) * ft_strlen(map->matrix[i]));
		if (!matrix[i])
			ft_freematrix(matrix, map);
		j = -1;
		while (map->matrix[i][++j])
			matrix[i][j] = map->matrix[i][j];
		matrix[i][j] = '\0';
	}
	matrix[i] = NULL;
	return (matrix);
}

static void	ft_fill(char **matrix, int y, int x)
{
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	if (ft_strchr("FEX1", matrix[y][x]) || matrix[y][x] == '\0')
		return ;
	else if (y < 0 || x < 0 || x > (int)ft_strlen(matrix[y]) || y >= i)
		return ;
	matrix[y][x] = 'F';
	ft_fill(matrix, y + 1, x);
	ft_fill(matrix, y, x + 1);
	ft_fill(matrix, y - 1, x);
	ft_fill(matrix, y, x - 1);
}

static void	ft_checkfill(char **matrix, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (matrix[i][j] == 'C')
			{
				ft_freematrix(matrix, NULL);
				ft_cleanmap("Collectable out of reach\n", map, FLOOD_ER);
			}
		}
	}
}
