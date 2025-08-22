/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:13:54 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/22 19:42:42 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
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

# ifndef TITLE_WD
#  define TITLE_WD 50
# endif

# ifndef TITLE_HG
#  define TITLE_HG 50
# endif

typedef struct s_map
{
	int		fd;
	int		size;
	char	**matrix;
	int		nb_c;
	int		nb_e;
	int		nb_p;
	int		pos_x;
	int		pos_y;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		bpp;
	char	*addr;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		movecount;
	t_map	*map;
	t_img	*player;
	t_img	*floor;
	t_img	*wall;
	t_img	*collect;
	t_img	*exit;
	t_img	*enemy;
}	t_game;

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

enum e_error_parse
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

enum e_error_game
{
	GAME_ALLOC,
};

/*Error and Cleaning Functions*/
void	ft_cleanmap(char *str, t_map *map, int mod);
void	ft_cleangame(char *str, t_game *game, int mod);

/*Parsing Functions*/
void	ft_floodfill(t_map *map, int y, int x);
void	ft_isber(char *argv, t_map *map);
void	ft_validchar(t_map *map);
void	ft_isrect(t_map *map);
void	ft_checkwall(t_map *map, size_t len);
void	ft_nbcheck(t_map *map);

/*Game Functions*/
void	ft_game(t_map *map);

#endif