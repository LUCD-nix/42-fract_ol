/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucorrei <lucorrei@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:47:27 by lucorrei          #+#    #+#             */
/*   Updated: 2025/07/16 13:47:31 by lucorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fract_ol.h"

double	atod_wrapper(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] != '\0')
	{
		ft_printf("Please provide float-like arguments for julia\n");
		ft_printf("(nothing of interest happens beyond (-)20.0)\n");
		exit(EXIT_FAILURE);
	}
	return (ft_atod(str));
}

void	parse_julia(int argc, char **argv, t_params *to_fill)
{
	to_fill->frac = &julia;
	if (argc == 2)
	{
		to_fill->power = 2.0;
		to_fill->c_re = -0.835;
		to_fill->c_im = -0.321;
		return ;
	}
	else if (argc != 5)
	{
		ft_printf(USAGE);
		exit(EXIT_FAILURE);
	}
	to_fill->power = atod_wrapper(argv[2]);
	to_fill->c_re = atod_wrapper(argv[3]);
	to_fill->c_im = atod_wrapper(argv[4]);
}

t_params	*parse_args(int argc, char **argv, t_params *to_fill)
{
	if (argc == 1)
	{
		ft_printf(USAGE);
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp(argv[1], "mandelbrot"))
		to_fill->frac = &mandelbrot;
	else if (!ft_strcmp(argv[1], "julia"))
	{
		parse_julia(argc, argv, to_fill);
	}
	else
	{
		ft_printf(USAGE);
		exit(EXIT_FAILURE);
	}
	return (to_fill);
}
