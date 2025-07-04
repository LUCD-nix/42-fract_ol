/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:54:14 by lucorrei          #+#    #+#             */
/*   Updated: 2025/07/03 15:54:19 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

double	julia(t_params *p)
{
	double	r;
	double	r2;
	double	theta;
	double	x;
	double y;
	int		i;


	i = -1;
	x = p->x0;
	y = p->y0;
	r = hypot(x, y);
	r2 = x * x + y * y;
	theta = atan2(y, x);
	while (r2 <= BAILOUT2 && ++i < MAX_ITER)
	{
		r2 = x * x + y * y;
		r = hypot(x, y);
		theta = atan2(y, x);
		x = pow(r, p->power) * cos(p->power * theta) + p->c;
		y = pow(r, p->power) * sin(p->power * theta) + p->c;
	}
	if (i == MAX_ITER)
		return (0);
	return (i - log(log(x * x + y * y)/log(BAILOUT))/log(p->power));
}
