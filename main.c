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

void	start_mlx(t_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		exit(EXIT_FAILURE);
	mlx_data->window = mlx_new_window(mlx_data->mlx, X_MAX, Y_MAX, "fract_ol");
	if (!mlx_data->window)
	{
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
		exit(EXIT_FAILURE);
	}
}

void	init_images(t_img *image1, t_img *image2, t_data *mlx_data)
{
	image1->img = mlx_new_image(mlx_data->mlx, X_MAX, Y_MAX);
	if (!image1->img)
	{
		mlx_destroy_window(mlx_data->mlx, mlx_data->window);
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
		exit(EXIT_FAILURE);
	}
	image1->addr = mlx_get_data_addr(image1->img, &image1->bits_per_pixel,
			&image1->line_length, &image1->endian);
	image2->img = mlx_new_image(mlx_data->mlx, X_MAX, Y_MAX);
	if (!image2->img)
	{
		mlx_destroy_image(mlx_data->mlx, &image1);
		mlx_destroy_window(mlx_data->mlx, mlx_data->window);
		mlx_destroy_display(mlx_data->mlx);
		free(mlx_data->mlx);
		exit(EXIT_FAILURE);
	}
	image2->addr = mlx_get_data_addr(image2->img, &image2->bits_per_pixel,
			&image2->line_length, &image2->endian);
}

void	populate_coords(t_img *img, double xc, double yc, double scale)
{
	img->scale = scale;
	img->center_x = xc;
	img->center_y = yc;
}

// TODO: make julia set somehow faster, careful of floating point rounding
// TODO: better argument parsing (ie non numeric chars)
int	main(int argc, char **argv)
{
	t_data		mlx_data;
	t_img		image1;
	t_img		image2;
	t_params	params;

	mlx_data.params = parse_args(argc, argv, &params);
	start_mlx(&mlx_data);
	init_images(&image1, &image2, &mlx_data);
	mlx_data.image_data = &image1;
	mlx_data.other_image = &image2;
	populate_coords(&image1, -0.75, 0, 1.0);
	apply_fractal(&image1, mlx_data.params);
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.window, image1.img, 0, 0);
	mlx_mouse_hook(mlx_data.window, &redraw_on_zoom, &mlx_data);
	mlx_key_hook(mlx_data.window, &escape_to_exit, &mlx_data);
	mlx_hook(mlx_data.window, 17, STRUCTURE_NOTIFY_MASK,
		&free_and_quit, &mlx_data);
	mlx_loop(mlx_data.mlx);
}
