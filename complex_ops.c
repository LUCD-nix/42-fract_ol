/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:36:56 by lucorrei          #+#    #+#             */
/*   Updated: 2025/06/24 17:36:59 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

inline t_complex	c_add(t_complex a, t_complex b)
{
	return ((t_complex) { a.re + b.re, a.im + b.im });
}

inline t_complex	c_sub(t_complex a, t_complex b)
{
	return ((t_complex) { a.re - b.re, a.im - b.im });
}

inline t_complex	c_mult(t_complex a, t_complex b)
{
	return ((t_complex)
		{ a.re * b.re - a.im * b.im,
		a.im * b.re + b.im * a.re});
}

inline double	c_mag(t_complex a)
{
	return (sqrt(a.re * a.re + a.im * a.im));
}
