/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:13:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/19 15:22:10 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifndef WIDTH
#  define WIDTH 1000
# endif

# ifndef HEIGHT
#  define HEIGHT 700
# endif

typedef struct s_map
{
	int		fd;
	int		size;
	char	**matrix;
	int		nb_c;
	int		nb_e;
	int		nb_p;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

enum e_error
{
	ALLOC,
	NO_ARG,
	FILE_FORM,
	OPEN_ER,
	MATRIX_ER,
	CHAR_ER,
	NB_ER,
	RECT_ER,
	FLOOD_ER
};

#endif