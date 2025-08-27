/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:11:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/27 11:03:44 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIDTH TITLE * map->len
#define HEIGHT TITLE * map->size

static t_game	*ft_gameinit(t_map *map);
static t_img	*ft_imginit(t_game *game, char *path);

static int	ft_exitgame(t_game *game)
{
	if (game)
		mlx_loop_end(game->mlx);
	return (0);
}

static int	render(t_game *game)
{
	int	x, y;

	if (!game->win || !game->mlx || !game)
		return 0;
	y = 0;
	while (y < game->map->size)
	{
		x = 0;
		while (x < game->map->len)
		{
			if (game->map->matrix[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor->img, x * TITLE, y * TITLE);
			if (game->map->matrix[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall->img, x * TITLE, y * TITLE);
			if (game->map->matrix[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collect->img, x * TITLE, y * TITLE);
			if (game->map->matrix[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit->img, x * TITLE, y * TITLE);
			if (game->map->matrix[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player->img, x * TITLE, y * TITLE);
			x++;
		}
		y++;
	}
	return 0;
}

static int	ft_keypress(int keysym, t_game *game)
{
	if (game && keysym == XK_Escape)
		mlx_loop_end(game->mlx);
	return (0);
}

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
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_cleanmap("Failed to allocate t_game\n", map, GAME_ALLOC);
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_cleangame("Failed to initialize display\n", game, GAME_ALLOC);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "so_long");
	if (!game->win)
		ft_cleangame("Failed to create window\n", game, GAME_ALLOC);
	game->map = map;
	game->collect = ft_imginit(game, "textures/collectable.xpm");
	if (!game->collect)
		ft_cleangame("Failed to allocate collectable\n", game, GAME_ALLOC);
	game->exit = ft_imginit(game, "textures/exit.xpm");
	if (!game->exit)
		ft_cleangame("Failed to allocate exit\n", game, GAME_ALLOC);
	game->floor = ft_imginit(game, "textures/floor.xpm");
	if (!game->floor)
		ft_cleangame("Failed to allocate floor\n", game, GAME_ALLOC);
	game->player = ft_imginit(game, "textures/player.xpm");
	if (!game->player)
		ft_cleangame("Failed to allocate player\n", game, GAME_ALLOC);
	game->wall = ft_imginit(game, "textures/wall.xpm");
	if (!game->wall)
		ft_cleangame("Failed to allocate wall\n", game, GAME_ALLOC);
	game->movecount = 0;
	return (game);
}

static t_img	*ft_imginit(t_game *game, char *path)
{
	t_img	*img;

	if (!game)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		perror(path);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (img);
}
