/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:29 by lucorrei          #+#    #+#             */
/*   Updated: 2025/07/04 18:03:33 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

/* 
** Colouring function based on https://www.shadertoy.com/view/4df3Rn
** main difference here is multiplying by 255 to get back an int
** and the self-explanatory bit shifting that follows
*/
void	colour_and_put(t_img *img, double iter, int px, int py)
{
	int	red;
	int	green;
	int	blue;
	int	colour;

	if (iter < 0.5)
		colour = 0x000000;
	else
	{
		red = (0.5 + 0.5 * cos(3.0 + iter * 0.15)) * 255;
		green = (0.5 + 0.5 * cos(3.0 + iter * 0.15 + 0.6)) * 255;
		blue = (0.5 + 0.5 * cos(3.0 + iter * 0.15 + 1.0)) * 255;
		colour = (red << 16) + (green << 8) + blue;
	}
	put_pixel_to_img(img, px, py, colour);
}

double	get_x_coord(int px, t_img *img)
{
	return (((double)px / img->x_max * 3.5
			- 1.75) * img->scale + img->center_x);
}

double	get_y_coord(int py, t_img *img)
{
	return (((double)py / img->y_max * 2
			- 1) * img->scale + img->center_y);
}

void	apply_fractal(t_img *img, t_params *p)
{
	int		px;
	int		py;
	double	(*fract)(t_params *p);
	double	iter;

	fract = p->frac;
	py = 0;
	while (py < img->y_max)
	{
		px = 0;
		p->y0 = get_y_coord(py, img);
		while (px < img->x_max)
		{
			p->x0 = get_x_coord(px, img);
			iter = fract(p);
			colour_and_put(img, iter, px, py);
			px++;
		}
		py++;
	}
}
