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
# define BAILOUT2 262144
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define ESCAPE 0xff1b
# define STRUCTURE_NOTIFY_MASK 1L << 17

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

typedef struct s_params {
	double x0;
	double y0;
	int	c;
	int	power;
} t_params;

typedef struct s_data {
	void		*mlx;
	void		*window;
	t_img		*image_data;
	t_img		*other_image;
	t_params	*params;
}	t_data;

void	put_pixel_to_img(t_img *data, int x, int y, int colour);
void	apply_fractal(t_img *img, double (*fract)(t_params *p), t_params *params);
void	populate_coords(t_img *img, double xc, double yc, double scale);

double	get_x_coord(int px, t_img *img);
double	get_y_coord(int py, t_img *img);

double	mandelbrot(t_params *p);
double	julia(t_params *c);

int	redraw_on_zoom(int button, int x, int y, void *ptr);
int		escape_to_exit(int keycode, void *param);
int		free_and_quit(t_data *data);

#endif // FRACTOL_H
