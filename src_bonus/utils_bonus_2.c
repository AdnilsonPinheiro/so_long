/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:58:47 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/04 18:28:12 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	**ft_estr(t_game *game)
{
	char	**res;

	res = malloc(4 * sizeof(char *));
	if (!res)
		ft_cleangame("Failed to allocate for enemies\n", game, GAME_ALLOC);
	res[0] = "textures/dog.xpm";
	res[1] = "textures/man.xpm";
	res[2] = "textures/lady.xpm";
	res[3] = NULL;
	return (res);
}

char	**ft_cstr(t_game *game)
{
	char	**res;

	res = malloc(4 * sizeof(char *));
	if (!res)
		ft_cleangame("Failed to allocate for items\n", game, GAME_ALLOC);
	res[0] = "textures/sushi_1.xpm";
	res[1] = "textures/sushi_2.xpm";
	res[2] = "textures/sushi_3.xpm";
	res[3] = NULL;
	return (res);
}
