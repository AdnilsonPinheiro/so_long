/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:11:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 17:07:37 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_game	*ft_gameinit(t_map *map);
static int		ft_exitgame(t_game *game);
static int		ft_keypress(int keysym, t_game *game);
static int		render(t_game *game);

void	ft_game(t_map *map)
{
	t_game	*game;

	game = ft_gameinit(map);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &ft_exitgame, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &ft_keypress, game);
	mlx_loop(game->mlx);
	ft_cleangame(NULL, game, 0);
}

static t_game	*ft_gameinit(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_cleangame("Failed to allocate t_game\n", game, GAME_ALLOC);
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_cleangame("Failed to initialize display\n", game, GAME_ALLOC);
	game->win = mlx_new_window(game->mlx, TITLE * map->len,
			TITLE * map->size, "so_long");
	if (!game->win)
		ft_cleangame("Failed to create window\n", game, GAME_ALLOC);
	ft_initallimg(game);
	game->map = map;
	game->movecount = 0;
	return (game);
}

static int	render(t_game *game)
{
	int	x;
	int	y;

	if (!game->win || !game->mlx || !game)
		return (0);
	if (game->map->nb_c == 0)
		ft_changeimg(game, game->exit, "textures/box_open.xpm");
	y = 0;
	while (y < game->map->size)
	{
		x = 0;
		while (x < game->map->len)
		{
			ft_put_to_window(game, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

static int	ft_keypress(int keysym, t_game *game)
{
	if (game && keysym == XK_Escape)
		mlx_loop_end(game->mlx);
	else if (game && (keysym == XK_w || keysym == XK_Up))
		ft_move_up(game);
	else if (game && (keysym == XK_s || keysym == XK_Down))
		ft_move_down(game);
	else if (game && (keysym == XK_a || keysym == XK_Left))
		ft_move_left(game);
	else if (game && (keysym == XK_d || keysym == XK_Right))
		ft_move_right(game);
	return (0);
}

static int	ft_exitgame(t_game *game)
{
	if (game && game->mlx)
		mlx_loop_end(game->mlx);
	return (0);
}
