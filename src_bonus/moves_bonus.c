/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:09:37 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/03 19:25:41 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_move_up(t_game *game)
{
	int	new;
	int	x;

	new = game->map->player_y - 1;
	x = game->map->player_x;
	if (game->map->matrix[new][x] == '1')
		return ;
	if (game->map->matrix[new][x] == 'C')
		game->map->nb_c--;
	if (game->map->matrix[new][x] == 'X')
		ft_cleangame("You we're killed =(\nBUT\n", game, 0);
	if (game->map->matrix[new][x] == 'E' && game->map->nb_c > 0)
		return ;
	if (game->map->matrix[new][x] == 'E' && game->map->nb_c == 0)
	{
		mlx_loop_end(game->mlx);
		return ;
	}
	game->map->matrix[new][x] = 'P';
	game->map->matrix[game->map->player_y][x] = '0';
	game->map->player_y -= 1;
	game->movecount++;
	ft_printf("Moves made: %d\n", game->movecount);
}

void	ft_move_down(t_game *game)
{
	int	new;
	int	x;

	new = game->map->player_y + 1;
	x = game->map->player_x;
	if (game->map->matrix[new][x] == '1')
		return ;
	if (game->map->matrix[new][x] == 'C')
		game->map->nb_c--;
	if (game->map->matrix[new][x] == 'X')
		ft_cleangame("You we're killed =(\nBUT\n", game, 0);
	if (game->map->matrix[new][x] == 'E' && game->map->nb_c > 0)
		return ;
	if (game->map->matrix[new][x] == 'E' && game->map->nb_c == 0)
	{
		mlx_loop_end(game->mlx);
		return ;
	}
	game->map->matrix[new][x] = 'P';
	game->map->matrix[game->map->player_y][x] = '0';
	game->map->player_y += 1;
	game->movecount++;
	ft_printf("Moves made: %d\n", game->movecount);
}

void	ft_move_left(t_game *game)
{
	int	new;
	int	y;

	new = game->map->player_x - 1;
	y = game->map->player_y;
	if (game->map->matrix[y][new] == '1')
		return ;
	if (game->map->matrix[y][new] == 'C')
		game->map->nb_c--;
	if (game->map->matrix[y][new] == 'X')
		ft_cleangame("You we're killed =(\nBUT\n", game, 0);
	if (game->map->matrix[y][new] == 'E' && game->map->nb_c > 0)
		return ;
	if (game->map->matrix[y][new] == 'E' && game->map->nb_c == 0)
	{
		mlx_loop_end(game->mlx);
		return ;
	}
	game->map->matrix[y][new] = 'P';
	game->map->matrix[y][game->map->player_x] = '0';
	game->map->player_x -= 1;
	game->movecount++;
	ft_changeimg(game, game->player, "textures/cat_left.xpm");
	ft_printf("Moves made: %d\n", game->movecount);
}

void	ft_move_right(t_game *game)
{
	int	new;
	int	y;

	new = game->map->player_x + 1;
	y = game->map->player_y;
	if (game->map->matrix[y][new] == '1')
		return ;
	if (game->map->matrix[y][new] == 'C')
		game->map->nb_c--;
	if (game->map->matrix[y][new] == 'X')
		ft_cleangame("You we're killed =(\nBUT\n", game, 0);
	if (game->map->matrix[y][new] == 'E' && game->map->nb_c > 0)
		return ;
	if (game->map->matrix[y][new] == 'E' && game->map->nb_c == 0)
	{
		mlx_loop_end(game->mlx);
		return ;
	}
	game->map->matrix[y][new] = 'P';
	game->map->matrix[y][game->map->player_x] = '0';
	game->map->player_x += 1;
	game->movecount++;
	ft_changeimg(game, game->player, "textures/cat_right.xpm");
	ft_printf("Moves made: %d\n", game->movecount);
}
