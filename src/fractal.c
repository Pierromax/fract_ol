/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:54:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/01/31 10:21:50 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(t_complex pos, t_image *img)
{
	int		i;
	double	real;
	double	imag;
	double	temp;

	real = pos.x;
	imag = pos.y;
	i = 0;
	while (i < img->max_iter)
	{
		temp = real * real - imag * imag + pos.x;
		imag = 2 * real * imag + pos.y;
		real = temp;
		if (real * real + imag * imag > 4)
			return (i);
		i++;
	}
	return (i);
}

int	julia(t_complex z, t_image *img)
{
	int		iter;
	double	tmp;

	iter = 0;
	while (iter < img-> max_iter && (z.x * z.x + z.y * z.y) < 4)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + img->jul_x;
		z.y = 2 * tmp * z.y + img->jul_y;
		iter++;
	}
	return (iter);
}

int	burning_ship(t_complex z, t_image *img)
{
	int		iter;
	double	tmp;
	double	x;
	double	y;

	iter = 0;
	x = z.x;
	y = z.y;
	while (iter < img->max_iter && (z.x * z.x + z.y * z.y) < 4)
	{
		tmp = fabs(z.x * z.x - z.y * z.y + x);
		z.y = fabs(2 * z.x * z.y) + y;
		z.x = tmp;
		iter++;
	}
	return (iter);
}
