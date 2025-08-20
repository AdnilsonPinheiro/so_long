/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:11:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/20 19:34:45 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_cleangame(char *str, t_game *game, int mod);
static void	ft_my_pixel_put(t_img *img, int x, int y, int color);
static int	handle_keypress(int keysym, t_game *game);

void	ft_game(t_map *map)
{
	t_game	*game;
	int	x = 200;
	int	y = 200;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_cleangame("Failed to allocate for t_game\n", NULL, GAME_ALLOC);
	game->map = map;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_cleangame("Failed to initialize\n", game, GAME_ALLOC);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "so_long");
	if (!game->win)
		ft_cleangame("Failed to create window\n", game, GAME_ALLOC);
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		ft_cleangame("Failed to allocate for t_img\n", game, GAME_ALLOC);
	game->img->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img->img)
		ft_cleangame("Failed to create image\n", game, GAME_ALLOC);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp, \
		&game->img->line_len, &game->img->endian);
	while (y <= 500)
	{
		x = 200;
		while (x <= 500)
		{
			ft_my_pixel_put(game->img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	printf("MLX: %p\n", game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_loop(game->mlx);
	ft_cleangame(NULL, game, 0);
}

static void	ft_my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + ((y * img->line_len) + (x * img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	handle_keypress(int keysym, t_game *game)
{
	printf("MLX: %p\n", game->mlx);
	if (keysym == XK_Escape)
		ft_cleangame(NULL, game, 0);
	return (0);
}

static void	ft_cleangame(char *str, t_game *game, int mod)
{
	if (str)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(str, 2);
	}
	if (game)
	{
		printf("Entrou\n");
		printf("MLX: %p\n", game->mlx);
		if (game->map)
			ft_cleanmap(NULL, game->map, 0);
		if (game->img)
		{
			if (game->img->img)
				mlx_destroy_image(game->mlx, game->img->img);
			free(game->img);
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			printf("limpando\n");
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
	if (mod != 0)
		exit(EXIT_FAILURE);
}
