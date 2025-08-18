/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:20:05 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/18 19:53:07 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_parse(char *argv, t_map *map);
static void	ft_isber(char *argv, t_map *map);
static void	ft_validchar(t_map *map);
static void	ft_size(char *argv, t_map *map);
static void	ft_makemap(char *argv, t_map *map);
static void	ft_cleanmap(char *str, t_map *map, int mod);
static void	ft_nbcheck(t_map *map);
static void	ft_isrect(t_map *map);
static void	ft_issolvable(t_map *map);
static void	ft_floodfill(t_map *map, int y, int x);

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
	ft_cleanmap(NULL, map, 0);
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
	ft_issolvable(map);
}

static void	ft_isber(char *argv, t_map *map)
{
	int	pos;

	map->matrix = NULL;
	map->fd = 0;
	if (!argv)
		ft_cleanmap("No argument\n", map, NO_ARG);
	pos = ft_strlen(argv) - 4;
	if (pos <= 0)
		ft_cleanmap("File format invalid\n", map, FILE_FORM);
	if (ft_strncmp(&argv[pos], ".ber", 4) != 0)
		ft_cleanmap("File format invalid\n", map, FILE_FORM);
}

static void	ft_size(char *argv, t_map *map)
{
	char	*line;

	map->size = 0;
	map->fd = open(argv, O_RDONLY);
	if (map->fd == -1)
		ft_cleanmap("Failed to open argv[1]\n", map, OPEN_ER);
	while ((line = get_next_line(map->fd)))
	{
		map->size++;
		free(line);
	}
	close(map->fd);
	free(line);
}

static void	ft_makemap(char *argv, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	map->matrix = malloc(sizeof(char *) * (map->size + 1));
	if (!map->matrix)
		ft_cleanmap("Failed to allocate for matrix\n", map,  MATRIX_ER);
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
	map->matrix[i] = NULL;
	close(map->fd);
}

static void	ft_validchar(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while(map->matrix[i])
	{
		j = 0;
		while(map->matrix[i][j])
		{
			if (map->matrix[i][j] == 'C')
				map->nb_c++;
			if (map->matrix[i][j] == 'P')
				map->nb_p++;
			if (map->matrix[i][j] == 'E')
				map->nb_e++;
			if (!ft_strchr("CPE01", map->matrix[i][j]))
				ft_cleanmap("Map has invalid elements\n", map, CHAR_ER);
			j++;
		}
		i++;
	}
	ft_nbcheck(map);
}

static void	ft_nbcheck(t_map *map)
{
	if (map->nb_c < 1)
		ft_cleanmap("Not enough collectables\n", map, NB_ER);
	else if (map->nb_e != 1)
		ft_cleanmap("Must have one, and only one, exit\n", map, NB_ER);
	else if (map->nb_p != 1)
		ft_cleanmap("Must have one, and only one, player\n", map, NB_ER);
}

static void	ft_isrect(t_map *map)/*verificar se as paredes estao certas*/
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(map->matrix[i]);
	while (map->matrix[i])
	{
		if (ft_strlen(map->matrix[i]) != len)
			ft_cleanmap("Map not rectangular\n", map, RECT_ER);
		i++;
	}
}

static void	ft_issolvable(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i++])
	{
		j = 0;
		while (map->matrix[i][j++])
		{
			if (map->matrix[i][j] == 'P')
			{
				ft_floodfill(map, i, j);
				return ;
			}
		}
	}
}

static void	ft_floodfill(t_map *map, int y, int x)
{
	char	**matrix;
	char	player;

	ft_memcpy(matrix, map->matrix, (size_t)map->size);
	player = matrix[y][x];
	if (player != "1")
	{
		matrix[++y][x] = player;
		matrix[y][++x] = player;
		matrix[--y][x] = player;
		matrix[y][--x] = player;
	}
}

static void	ft_cleanmap(char *str, t_map *map, int mod)
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
