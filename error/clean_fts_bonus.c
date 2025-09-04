/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fts_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:36:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/04 15:05:59 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_cleanmap(char *str, t_map *map, int mod)
{
	int	i;

	if (str)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(str, 2);
	}
	if (map)
	{
		if (map->matrix)
		{
			i = 0;
			while (map->matrix[i])
				free(map->matrix[i++]);
			free(map->matrix);
		}
		if (map->fd > -1)
			close(map->fd);
		free(map);
	}
	if (mod != 0)
		exit(EXIT_FAILURE);
}

void	ft_cleangame(char *str, t_game *game, int mod)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (game)
	{
		if (game->map)
			ft_cleanmap(NULL, game->map, 0);
		ft_clean_all_img(game);
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			game->mlx = NULL;
		}
		free(game);
	}
	if (mod != 0 && mod != INT_MAX)
		exit(EXIT_FAILURE);
	if (mod == INT_MAX)
		exit(EXIT_SUCCESS);
}

void	ft_clean_all_img(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->exit)
		ft_cleanimg(game, game->exit);
	if (game->floor)
		ft_cleanimg(game, game->floor);
	if (game->player)
		ft_cleanimg(game, game->player);
	if (game->wall)
		ft_cleanimg(game, game->wall);
	i = -1;
	while (++i < ENEMY_COUNT)
		ft_cleanimg(game, game->enemy[i]);
	i = -1;
	while (++i < COLLECT_COUNT)
		ft_cleanimg(game, game->collect[i]);
}

void	ft_cleanimg(t_game *game, t_img *img)
{
	if (!img)
		return ;
	if (img->img && game->mlx)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
	}
	free(img);
}

void	ft_freematrix(char **matrix, t_map *map)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	if (map)
		ft_cleanmap("Failed to copy map->matrix\n", map, FLOOD_ER);
}
