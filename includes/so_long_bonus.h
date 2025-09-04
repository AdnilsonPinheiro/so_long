/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:05:07 by adpinhei          #+#    #+#             */
/*   Updated: 2025/09/04 18:29:57 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifndef TITLE
#  define TITLE 48
# endif

# ifndef COLLECT_COUNT
#  define COLLECT_COUNT 3
# endif

# ifndef ENEMY_COUNT
#  define ENEMY_COUNT 3
# endif

typedef struct s_map
{
	int		fd;
	int		size;
	int		len;
	char	**matrix;
	int		nb_c;
	int		nb_e;
	int		nb_p;
	int		nb_x;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		bpp;
	char	*addr;
	int		line_len;
	int		endian;
	int		width;
	int		height;
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
	t_img	*collect[COLLECT_COUNT];
	t_img	*exit;
	t_img	*enemy[ENEMY_COUNT];
}	t_game;

enum e_error_parse
{
	ALLOC = 1,
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
	GAME_ALLOC = 1,
	IMG_CHANGE,
	KILL_ER
};

/*Error and Cleaning Functions*/
void	ft_cleanmap(char *str, t_map *map, int mod);
void	ft_freematrix(char **matrix, t_map *map);
void	ft_cleangame(char *str, t_game *game, int mod);
void	ft_clean_all_img(t_game *game);
void	ft_cleanimg(t_game *game, t_img *img);

/*Parsing Functions*/
void	ft_floodfill(t_map *map, int y, int x);
void	ft_isber(char *argv, t_map *map);
void	ft_validchar(t_map *map);
void	ft_isrect(t_map *map);
void	ft_checkwall(t_map *map, size_t len);
void	ft_nbcheck(t_map *map);
void	ft_fillexit(char **matrix, int y, int x);
void	ft_checkexit(char **matrix, t_map *map);

/*Game Functions*/
void	ft_game(t_map *map);

/*Image Functions*/
void	ft_initallimg(t_game *game);
t_img	*ft_imginit(t_game *game, char *path);
void	ft_put_to_window(t_game *game, int x, int y);
void	ft_changeimg(t_game *game, t_img *img, char *path);
void	ft_initarr(t_game *game, t_img *img[], char *path[], int size);

/*Movement Functions*/
void	ft_move_up(t_game *game);
void	ft_move_down(t_game *game);
void	ft_move_left(t_game *game);
void	ft_move_right(t_game *game);

/*Utils*/
int		lcg_rand(void);
void	ft_rand_collect(t_game *game, int x, int y);
void	ft_rand_enemy(t_game *game, int x, int y);
char	**ft_estr(t_game *game);
char	**ft_cstr(t_game *game);

#endif