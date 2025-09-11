/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:20:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/11 15:55:04 by adpinhei         ###   ########.fr       */
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
		ft_putstr_fd("Error\nTry ./so_long maps/map.ber\n", 2);
		return (1);
	}
	ft_parse(argv[1], map);
	ft_game(map);
	ft_putstr_fd("Program closed gracefully =)\n", 1);
}
/// @brief summarizes all parsing functions
/// @param argv the .ber file passed as parameter
/// @param map the t_map struct that will hold all map info
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
/// @brief finds the size of the map to be allocated
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
	map->fd = -1;
}
/// @brief creates a map inside the struct based on the .ber file
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
	map->len = ft_strlen(map->matrix[0]);
	close(map->fd);
	map->fd = -1;
}
/// @brief finds the 'P' char
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
				map->player_y = i;
				map->player_x = j;
				ft_floodfill(map, i, j);
				return ;
			}
		}
	}
}
