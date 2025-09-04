/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:12:21 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/04 18:28:37 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_initallimg(t_game *game)
{
	char	**e_img;
	char	**c_img;

	if (!game)
		return ;
	e_img = ft_estr(game);
	c_img = ft_cstr(game);
	ft_initarr(game, game->collect, c_img, COLLECT_COUNT);
	ft_initarr(game, game->enemy, e_img, ENEMY_COUNT);
	free(e_img);
	free(c_img);
	game->exit = ft_imginit(game, "textures/box_closed.xpm");
	if (!game->exit)
		ft_cleangame("Failed to allocate exit\n", game, GAME_ALLOC);
	game->floor = ft_imginit(game, "textures/floor_tatami.xpm");
	if (!game->floor)
		ft_cleangame("Failed to allocate floor\n", game, GAME_ALLOC);
	game->player = ft_imginit(game, "textures/cat_right.xpm");
	if (!game->player)
		ft_cleangame("Failed to allocate player\n", game, GAME_ALLOC);
	game->wall = ft_imginit(game, "textures/bamboo.xpm");
	if (!game->wall)
		ft_cleangame("Failed to allocate wall\n", game, GAME_ALLOC);
}

t_img	*ft_imginit(t_game *game, char *path)
{
	t_img	*img;

	if (!game || !game->mlx)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	ft_bzero(img, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		perror(path);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (img);
}

void	ft_put_to_window(t_game *game, int x, int y)
{
	if (!game || !game->map || !game->map->matrix)
		return ;
	if (game->map->matrix[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->floor->img,
			x * TITLE, y * TITLE);
	if (game->map->matrix[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall->img,
			x * TITLE, y * TITLE);
	if (game->map->matrix[y][x] == 'C')
		ft_rand_collect(game, x, y);
	if (game->map->matrix[y][x] == 'X')
		ft_rand_enemy(game, x, y);
	if (game->map->matrix[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit->img,
			x * TITLE, y * TITLE);
	if (game->map->matrix[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player->img,
			x * TITLE, y * TITLE);
}

void	ft_changeimg(t_game *game, t_img *img, char *path)
{
	if (!game || !img || !path)
		return ;
	if (img->img)
		mlx_destroy_image(game->mlx, img->img);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
		ft_cleangame("Failed to change image\n", game, IMG_CHANGE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}

void	ft_initarr(t_game *game, t_img *img[], char *path[], int size)
{
	int	i;

	if (!game || !img || !path)
		return ;
	i = 0;
	while (i < size)
	{
		img[i] = ft_imginit(game, path[i]);
		if (!img[i])
			ft_cleangame("Failed to attribute image\n", game, GAME_ALLOC);
		i++;
	}
}
