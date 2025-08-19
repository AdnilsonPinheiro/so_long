/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:36:44 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/19 19:38:26 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_cleanmap(char *str, t_map *map, int mod)
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
