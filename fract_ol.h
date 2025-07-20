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
#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "minilibx-linux/mlx.h"
# include "42-libft/libft.h"
# include <stdlib.h>
# include <math.h>

# define MAX_ITER 600
# define BAILOUT 32
# define BAILOUT2 1024
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define ESCAPE 0xff1b
# define LEFT 0xff51
# define UP 0xff52
# define RIGHT 0xff53
# define DOWN 0xff54

# define STRUCTURE_NOTIFY_MASK 131072

# define USAGE "Usage: ./fract_ol [mandelbrot/julia] (if julia:[power]\
	[c_re] [c_im])\n"
# define X_MAX 854
# define Y_MAX 480

typedef struct s_params
{
	double	x0;
	double	y0;
	double	c_re;
	double	c_im;
	double	power;
	double	(*frac)(struct s_params *args);
}	t_params;

typedef struct s_img
{
	void	*img;
	char	*addr;
	double	scale;
	double	center_x;
	double	center_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_img		*image_data;
	t_img		*other_image;
	t_params	*params;
}	t_data;

void		put_pixel_to_img(t_img *data, int x, int y, int colour);
void		apply_fractal(t_img *img, t_params *p);
void		populate_coords(t_img *img, double xc, double yc, double scale);

double		get_x_coord(int px, t_img *img);
double		get_y_coord(int py, t_img *img);

double		mandelbrot(t_params *p);
double		julia(t_params *c);

t_params	*parse_args(int argc, char **argv, t_params *to_fill);
int			redraw_on_zoom(int button, int x, int y, void *ptr);
int			escape_to_exit(int keycode, void *param);
int			move_around_arrows(int keycode, void *param);
int			free_and_quit(t_data *data);

#endif // FRACT_OL_H
