/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:36:39 by lucorrei          #+#    #+#             */
/*   Updated: 2025/06/24 17:36:51 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>

# define MAX_ITER 1000
# define BAILOUT 512
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5


typedef struct	s_img {
	void	*img;
	char	*addr;
	double	scale;
	double	center_x;
	double	center_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x_max;
	int		y_max;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*window;
	t_img	*image_data;
}	t_data;

void	put_pixel_to_img(t_img *data, int x, int y, int colour);
void	apply_fractal(t_img *img, int max_x, int max_y, double (*fract)(double, double));

double	mandelbrot(double x0, double y0);

#endif // FRACTOL_H
