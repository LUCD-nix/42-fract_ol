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

int	redraw_on_zoom(int button, int x, int y, void *ptr)
{
	t_data	*mlx;
	t_img	*temp;
	double	scale;

	mlx = ptr;
	scale = 1;
	if (button == MOUSE_SCROLL_UP)
		scale *= 1.2;
	else if (button == MOUSE_SCROLL_DOWN)
		scale /= 1.2;
	populate_coords(mlx->other_image,
		get_x_coord(x, mlx->image_data),
		get_y_coord(y, mlx->image_data),
		mlx->image_data->scale / scale);
	apply_fractal(mlx->other_image, mlx->params);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->other_image->img, 0, 0);
	temp = mlx->image_data;
	mlx->image_data = mlx->other_image;
	mlx->other_image = temp;
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
	return (0);
}
