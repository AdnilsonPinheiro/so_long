/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:36:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/26 20:16:13 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (map->fd)
			close(map->fd);
		free(map);
	}
	if (mod != 0)
		exit(EXIT_FAILURE);
}

void	ft_cleangame(char *str, t_game *game, int mod)
{
	if (str)
	{
		ft_putstr_fd("Error!\n", 2);
		ft_putstr_fd(str, 2);
	}
	if (game)
	{
		mlx_loop_end(game->mlx);
		if (game->map)
			ft_cleanmap(NULL, game->map, 0);
		if (game->player && game->player->img)
			ft_cleanimg(game, game->player);
		if (game->floor && game->floor->img)
			ft_cleanimg(game, game->floor);
		if (game->collect && game->collect->img)
			ft_cleanimg(game, game->collect);
		if (game->enemy && game->enemy->img)
			ft_cleanimg(game, game->enemy);
		if (game->wall && game->wall->img)
			ft_cleanimg(game, game->wall);
		if (game->exit && game->exit->img)
			ft_cleanimg(game, game->exit);
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
	if (mod != 0)
		exit(EXIT_FAILURE);
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
