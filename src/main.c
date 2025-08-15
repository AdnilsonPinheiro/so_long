/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:06:32 by adpinhei          #+#    #+#             */
/*   Updated: 2025/08/15 17:28:04 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000
#define GREEN_PXL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

static int	handle_keypress(int keysym, t_data *data);
static int	render(t_data *data);
static int	render_rect(t_data *data, t_rect rect);
static void	render_backgrd(t_data *data, int color);

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "so_long");
	if (!data.win_ptr)
	{
		free(data.mlx_ptr);
		return (MLX_ERROR);
	}
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

static int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

static int	render(t_data *data)
{
	if (data->win_ptr)
	{
		render_backgrd(data, WHITE_PIXEL);
		render_rect(data, (t_rect){WIDTH-100, HEIGHT-100, 100, 100, GREEN_PXL});
		render_rect(data, (t_rect){0, 0, 500, 500, RED_PIXEL});
	}
	return (0);
}

static int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	if (!data->win_ptr)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		i++;
	}
	return (0);
}

static void	render_backgrd(t_data *data, int color)
{
	int	i;
	int	j;

	if (!data->win_ptr)
		return ;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
		i++;
	}
}