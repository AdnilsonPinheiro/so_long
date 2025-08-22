/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:11:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/22 19:57:18 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game	*ft_gameinit(t_map *map);
static t_img	*ft_imginit(t_game *game, t_img *img);

void	ft_game(t_map *map)
{
	t_game	*game;

	game = ft_gameinit(map);
}

static t_game	*ft_gameinit(t_map *map)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_cleanmap("Failed to allocate t_game\n", map, GAME_ALLOC);
	game->map = map;
	game->collect = ft_imginit(game, &game->collect);
	if (!game->collect)
		ft_cleangame("Failed to allocate collectable\n", game, GAME_ALLOC);
	game->exit = ft_imginit(game, &game->exit);
	if (!game->exit)
		ft_cleangame("Failed to allocate exit\n", game, GAME_ALLOC);
	game->floor = ft_imginit(game, &game->floor);
	if (!game->floor)
		ft_cleangame("Failed to allocate floor\n", game, GAME_ALLOC);
	game->player = ft_imginit(game, &game->player);
	if (!game->player)
		ft_cleangame("Failed to allocate player\n", game, GAME_ALLOC);
	game->wall = ft_imginit(game, &game->wall);
	if (!game->wall)
		ft_cleangame("Failed to allocate wall\n", game, GAME_ALLOC);
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_cleangame("Failed to initialize display\n", game, GAME_ALLOC);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "so_long");
	if (!game->win)
		ft_cleangame("Failed to create window\n", game, GAME_ALLOC);
	return (game);
}

static t_img	*ft_imginit(t_game *game, t_img *img)/*add image path*/
{
	if (!game)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(game->mlx, TITLE_WD, TITLE_HG);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}
