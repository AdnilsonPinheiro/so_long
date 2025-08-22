/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:36:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/22 19:59:52 by adpinhei         ###   ########.fr       */
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
		if (game->map)
			ft_cleanmap(NULL, game->map, 0);
		if (game->player)
			ft_cleanimg(game, game->player);
		if (game->floor)
			ft_cleanimg(game, game->floor);
		if (game->collect)
			ft_cleanimg(game, game->collect);
		if (game->enemy)
			ft_cleanimg(game, game->enemy);
		if (game->wall)
			ft_cleanimg(game, game->wall);
		if (game->exit)
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
