/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:50:52 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/19 20:05:33 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_isber(char *argv, t_map *map)
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

void	ft_validchar(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
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

void	ft_isrect(t_map *map)
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
	ft_checkwall(map, len - 1);
}

void	ft_checkwall(t_map *map, size_t len)
{
	int	i;

	i = -1;
	while (map->matrix[0][++i])
	{
		if (map->matrix[0][i] != '1')
			ft_cleanmap("Map must be surrounded by walls\n", map, RECT_ER);
	}
	i = 0;
	while (map->matrix[++i])
	{
		if (map->matrix[i][0] != '1' || map->matrix[i][len] != '1')
			ft_cleanmap("Map must be surrounded by walls\n", map, RECT_ER);
	}
	i = -1;
	while (map->matrix[map->size - 1][++i])
	{
		if (map->matrix[map->size - 1][i] != '1')
			ft_cleanmap("Map must be surrounded by walls\n", map, RECT_ER);
	}
}

void	ft_nbcheck(t_map *map)
{
	if (map->nb_c < 1)
		ft_cleanmap("Not enough collectables\n", map, NB_ER);
	else if (map->nb_e != 1)
		ft_cleanmap("Must have one, and only one, exit\n", map, NB_ER);
	else if (map->nb_p != 1)
		ft_cleanmap("Must have one, and only one, player\n", map, NB_ER);
}
