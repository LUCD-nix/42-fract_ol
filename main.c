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
#include "minilibx-linux/mlx.h"

void	put_pixel_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_image(t_img *image, t_data *mlx_data)
{
	image->x_max = 1920;
	image->y_max = 1080;
	image->img = mlx_new_image(mlx_data->mlx, image->x_max, image->y_max);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length,
		  					&image->endian);
}

void	populate_coords(t_img *img, double xc, double yc, double scale)
{
	img->scale = scale;
	img->center_x = xc;
	img->center_y = yc;
}

int	redraw_on_zoom(int button, int x, int y, void *param)
{
	t_data	*mlx;
	t_img	*temp;

	mlx = param;
	if (button == MOUSE_SCROLL_UP)
	{
		populate_coords(mlx->other_image,
			get_x_coord(x, mlx->image_data),
			get_y_coord(y, mlx->image_data),
			mlx->image_data->scale / 1.1);
		apply_fractal(mlx->other_image, mlx->other_image->x_max,
			mlx->other_image->y_max, &mandelbrot);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->other_image->img, 0, 0);
		temp = mlx->image_data;
		mlx->image_data = mlx->other_image;
		mlx->other_image = temp;
	}
	return (0);
}

int	main(void)
{
	t_data	mlx_data;
	t_img	image1;
	t_img	image2;

	mlx_data.mlx = mlx_init();
	init_image(&image1, &mlx_data);
	init_image(&image2, &mlx_data);
	mlx_data.window = mlx_new_window(mlx_data.mlx,
								 image1.x_max, image1.y_max,
								 "Hello world!");
	mlx_data.image_data = &image1;
	mlx_data.other_image = &image2;
	populate_coords(&image1, -0.75, 0, 1.0);
	apply_fractal(&image1, image1.x_max, image1.y_max, &mandelbrot);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.window, image1.img, 0, 0);
	mlx_mouse_hook(mlx_data.window, &redraw_on_zoom, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
