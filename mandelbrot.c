/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:38:09 by lucorrei          #+#    #+#             */
/*   Updated: 2025/07/01 15:38:18 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

/*
** Compute the smooth colour gradient outside of mandelbrot
** The first two if statements skip computation inside of the
** two main bulbs of the set.
** see : https://iquilezles.org/articles/mset1bulb
** and   https://iquilezles.org/articles/mset2bulb
**
** To determine the colour we use the following fact:
** When the bailout is big we have f(zn) is (to the first order)
** between B and B ** p which allows us to colour smoothly
** by substracting the distance to B and normalizing
** We can use log2 here by pure chance since our first order is p = 2
** and it diverges for mag > 2; Without this the formula would be:
** res = i - log(log(length(z))/log(B))/log(2.0)
*/
double	mandelbrot(t_params *p)
{
	double	x;
	double	y;
	double	xtemp;
	double	z2;
	int		i;

	x = 0;
	y = 0;
	i = -1;
	z2 = p->x0 * p->x0 + p->y0 * p->y0;
	if (256.0 * z2 * z2 - 96.0 * z2 + 32.0 * p->x0 - 3.0 < 0.0)
		return (0.0);
	if (16.0 * (z2 + 2.0 * p->x0 + 1.0) - 1.0 < 0.0)
		return (0.0);
	while (x * x + y * y <= BAILOUT2 && ++i < MAX_ITER)
	{
		xtemp = x * x - y * y + p->x0;
		y = (x + x) * y + p->y0;
		x = xtemp;
	}
	if (i == MAX_ITER)
		return (0);
	return (i - log2(log2(x * x + y * y)) + 4.0);
}
