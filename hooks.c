/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:56:51 by lucorrei          #+#    #+#             */
/*   Updated: 2025/07/01 15:56:54 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>

static inline void	swap_images(t_data *data)
{
	t_img	*temp;

	temp = data->image_data;
	data->image_data = data->other_image;
	data->other_image = temp;
}

int	redraw_on_zoom(int button, int x, int y, void *ptr)
{
	t_data	*mlx;
	double	scale;

	mlx = ptr;
	scale = 1;
	if (button == MOUSE_SCROLL_UP)
		scale *= 1.2;
	else if (button == MOUSE_SCROLL_DOWN)
		scale /= 1.2;
	if (scale != 1)
	{
		populate_coords(mlx->other_image,
			get_x_coord(x, mlx->image_data),
			get_y_coord(y, mlx->image_data),
			mlx->image_data->scale / scale);
		apply_fractal(mlx->other_image, mlx->params);
		mlx_put_image_to_window(mlx->mlx, mlx->window,
			mlx->other_image->img, 0, 0);
		swap_images(mlx);
	}
	return (0);
}

int	free_and_quit(t_data *data)
{
	void	*mlx;
	t_img	*image_data;
	t_img	*other_image;

	image_data = data->image_data;
	other_image = data->other_image;
	mlx = data->mlx;
	mlx_destroy_image(mlx, image_data->img);
	mlx_destroy_image(mlx, other_image->img);
	mlx_destroy_window(mlx, data->window);
	mlx_destroy_display(mlx);
	free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	escape_to_exit(int keycode, void *param)
{
	if (keycode == ESCAPE)
	{
		free_and_quit(param);
	}
	else if (keycode >= LEFT && keycode <= DOWN)
		move_around_arrows(keycode, param);
	return (0);
}

int	move_around_arrows(int keycode, void *param)
{
	t_data	*data;
	double	x;
	double	y;

	data = param;
	x = data->image_data->center_x;
	y = data->image_data->center_y;
	if (keycode == LEFT)
		x -= 0.2 * data->image_data->scale;
	if (keycode == RIGHT)
		x += 0.2 * data->image_data->scale;
	if (keycode == DOWN)
		y += 0.2 * data->image_data->scale;
	if (keycode == UP)
		y -= 0.2 * data->image_data->scale;
	populate_coords(data->other_image, x, y, data->image_data->scale);
	apply_fractal(data->other_image, data->params);
	mlx_put_image_to_window(data->mlx, data->window,
		data->other_image->img, 0, 0);
	swap_images(data);
	return (1);
}
