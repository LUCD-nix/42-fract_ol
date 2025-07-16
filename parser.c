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
		if (argc != 4)
		{
			ft_printf(USAGE);
			exit(EXIT_FAILURE);
		}
		to_fill->power = atod_wrapper(argv[2]);
		to_fill->c = atod_wrapper(argv[3]);
		to_fill->frac = &julia;
	}
	else
	{
		ft_printf(USAGE);
		exit(EXIT_FAILURE);
	}
	return (to_fill);
}
