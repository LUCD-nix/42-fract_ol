#include "fract_ol.h"

double	mandelbrot_inner(double x0, double y0)
{
	double	x;
	double	y;
	double	xtemp;
	double	nu;
	double	res;
	int		i;

	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= BAILOUT && ++i < MAX_ITER)
	{
		// TODO : consider defining x2 y2 to avoid squaring twice
		xtemp = x * x - y * y + x0;
		y = (x + x) * y + y0;
		x = xtemp;
	}
	if (i < MAX_ITER)
	{
		// It is fortuitous that we can use log base 2 here
		// it just so happens that we're interested in 
		// complex args between 0 and 2 (inner log)
		// and that P in f(z) = z**P + c is also 2 (outer log)
		// (see wikipedia for reference)
		// either way, it should be the fast
		nu = log2(log2(x * x + y * y) / 2);
		res = i + 1 - nu;
	}
	else
		res = (double)i;
	return (res);
}

void	colour_and_put(t_data *img, double iter, int px, int py)
{
	int	palette[19] = { 0x181825, 0x1e1e2e, 0x585b70, 0xbac2de, 0xcdd6f4, 0xb4befe, 0x89b4fa, 0x74c7ec, 0x89dceb, 0x94e2d5, 0xa6e3a1, 0xf9e2af, 0xfab387, 0xeba0ac, 0xf38ba8, 0xcba6f7, 0xf5c2e7, 0xf2cdcd, 0xf5e0dc };
	int	colour1;
	int	colour2;
	int	colour;

	iter = fmod(iter, 20);
	colour1 = palette[(int)floor(iter)];
	colour2 = palette[(int)ceil(iter) % 20];
	colour = colour1 + fmod(iter, 1) * (colour2 - colour1);
	put_pixel_to_img(img, px, py, colour);
}

double	get_x_coord(int px, t_data *img)
{
	double res;

	(void) img;
	res = (double)px / 1920.0 * 3.5 - 2.5;
	return (res);
}

// TODO : use img to properly scale the points, also rotation is wrong
double	get_y_coord(int py, t_data *img)
{
	double res;

	(void) img;
	res = (double)py / 1080.0 * 2.0 - 1;
	return (res);
}

void	mandelbrot(t_data *img, int max_x, int max_y)
{
	int		px;
	int		py;
	double	iter;
	double	x0;
	double	y0;

	py = 0;
	while (py < max_y)
	{
		px = 0;
		y0 = get_y_coord(py, img);
		while (px < max_x)
		{
			x0 = get_x_coord(px, img);
			iter = mandelbrot_inner(x0, y0);
			colour_and_put(img, iter, px, py);
			px++;
		}
		py++;
	}
}
