/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:37:12 by lucorrei          #+#    #+#             */
/*   Updated: 2025/06/24 17:37:19 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

void	put_pixel_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// int	redraw_on_zoom(int button, int x, int y, void *param)
// {
// 	t_img *img;
//
// 	img = param;
// 	if (button == MOUSE_SCROLL_UP)
// 	{
//
// 	}
// }
//
int	main(void)
{
	t_data	mlx_data;
	t_img	image;

	image.x_max = 1920;
	image.y_max = 1080;
	mlx_data.mlx = mlx_init();
	mlx_data.window = mlx_new_window(mlx_data.mlx,
								 image.x_max, image.y_max,
								 "Hello world!");
	image.img = mlx_new_image(mlx_data.mlx, 1920, 1080);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length,
								&image.endian);
	mlx_data.image_data = &image;
	apply_fractal(&image, image.x_max, image.y_max, &mandelbrot);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.window, image.img, 0, 0);
	// mlx_mouse_hook(mlx_data.window, &redraw_on_zoom, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
