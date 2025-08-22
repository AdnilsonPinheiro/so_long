/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:20:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/22 18:51:28 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_parse(char *argv, t_map *map);
static void	ft_size(char *argv, t_map *map);
static void	ft_makemap(char *argv, t_map *map);
static void	ft_findplayer(t_map *map);

int	main(int argc, char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_cleanmap("Failed to allocate for t_map *map\n", NULL, ALLOC);
	if (argc != 2)
	{
		ft_putstr_fd("Error\nTry ./so_long map.ber\n", 2);
		return (1);
	}
	ft_parse(argv[1], map);
	ft_game(map);
	ft_putstr_fd("Program closed gracefully =)\n", 1);
}

static void	ft_parse(char *argv, t_map *map)
{
	map->nb_c = 0;
	map->nb_e = 0;
	map->nb_p = 0;
	ft_isber(argv, map);
	ft_size(argv, map);
	ft_makemap(argv, map);
	ft_validchar(map);
	ft_isrect(map);
	ft_findplayer(map);
}

static void	ft_size(char *argv, t_map *map)
{
	char	*line;

	map->fd = open(argv, O_RDONLY);
	if (map->fd == -1)
		ft_cleanmap("Failed to open argv[1]\n", map, OPEN_ER);
	line = get_next_line(map->fd);
	free(line);
	map->size = 1;
	while (1)
	{
		line = get_next_line(map->fd);
		if (!line)
			break ;
		map->size++;
		free(line);
	}
	get_next_line_clear();
	close(map->fd);
}

static void	ft_makemap(char *argv, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	map->matrix = malloc(sizeof(char *) * (map->size + 1));
	if (!map->matrix)
		ft_cleanmap("Failed to allocate for matrix\n", map, MATRIX_ER);
	map->fd = open(argv, O_RDONLY);
	if (map->fd == -1)
		ft_cleanmap("Failed to open argv[1]\n", map, OPEN_ER);
	while (i < map->size)
	{
		line = get_next_line(map->fd);
		map->matrix[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
	}
	get_next_line_clear();
	map->matrix[i] = NULL;
	close(map->fd);
}

static void	ft_findplayer(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->matrix[++i])
	{
		j = -1;
		while (map->matrix[i][++j])
		{
			if (map->matrix[i][j] == 'P')
			{
				map->pos_y = i;
				map->pos_x = j;
				ft_floodfill(map, i, j);
				return ;
			}
		}
	}
}
