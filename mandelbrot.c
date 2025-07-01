#include "fract_ol.h"

double	mandelbrot_inner(double x0, double y0)
{
	double	x;
	double	y;
	double	xtemp;
	double	nu;
	double	res;
	double	z2;
	int		i;

	x = 0;
	y = 0;
	i = -1;
	z2 = x0 * x0 + y0 * y0;
	// skip computation inside M1 - https://iquilezles.org/articles/mset1bulb
	if (256.0 *z2 * z2 - 96.0 * z2 + 32.0 * x0 - 3.0 < 0.0 )
		return (0.0);
	// skip computation inside M2 - https://iquilezles.org/articles/mset2bulb
	if (16.0 * (z2 + 2.0* x0 + 1.0) - 1.0 < 0.0 )
		return (0.0);

		
	while (x * x + y * y <= BAILOUT && ++i < MAX_ITER)
	{
		xtemp = x * x - y * y + x0;
		y = (x + x) * y + y0;
		x = xtemp;
	}
	if (i < MAX_ITER)
	{
		// When the bailout is big we have f(zn) is (to the first order)
		// between B and B ** p which allows us to colour smoothly
		// by substracting the distance to B and normalizing
		// we can use log2 here by pure chance since our first order is 2
		// and it diverges for mag > 2
		// nu = i - log(log(length(z))/log(B))/log(2.0);
		nu = i - log2(log2(x * x + y * y)) + 4.0;
		res = i + 1 - nu;
	}
	else
		res = (double)i;
	return (res);
}
int	interpolate_rgb(int colour1, int colour2, double frac)
{
	int	red1;
	int	green1;
	int	blue1;
	int	red2;
	int	green2;
	int	blue2;
	int	res;

	red1 = colour1 >> 16 & 0xFF;
	green1 = colour1 >> 8 & 0xFF;
	blue1 = colour1 & 0xFF;
	red2 = colour2 >> 16 & 0xFF;
	green2 = colour2 >> 8 & 0xFF;
	blue2 = colour2 & 0xFF;
	res = 0;
	res += (int)(red1 + frac * (red2 - red1)) << 16;
	res += (int)(green1 + frac * (green2 - green1)) << 8;
	res += (int)(blue1 + frac * (blue2 - blue1));
	return (res);
}

// TODO: create a practical colouring function, base on https://www.shadertoy.com/view/4df3Rn
void	colour_and_put(t_data *img, double iter, int px, int py)
{
	int	red;
	int	green;
	int	blue;
	int	colour;

	if (iter < 0.5)
		colour = 0x000000;
	else
	{
		red = 0.5 + 0.5 * cos(3.0 + iter * 0.15) * 255;
		green = 0.5 + 0.5 * cos(3.0 + iter * 0.15 + 0.6) * 255;
		blue = 0.5 + 0.5 * cos(3.0 + iter * 0.15 + 1.0) * 255;
		colour = (red << 16) + (green << 8) + blue;
	}
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
