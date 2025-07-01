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


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	put_pixel_to_img(t_data *data, int x, int y, int colour);
void	apply_fractal(t_data *img, int max_x, int max_y, double (*fract)(double, double));

double	mandelbrot(double x0, double y0);

#endif // FRACTOL_H
