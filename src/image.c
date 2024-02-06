/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:06:09 by ple-guya          #+#    #+#             */
/*   Updated: 2024/02/04 21:40:05 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	fill_image(t_image *img)
{
	if (img->fractal[0] == 'M')
		draw_mandelbrot(img);
	if (img->fractal[0] == 'J')
		draw_julia(img);
	if (img->fractal[0] == 'B')
		draw_burn(img);
}

void	draw_mandelbrot(t_image *img)
{
	t_complex	z;
	int			x;
	int			y;
	int			iter;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z.x = (x - WIDTH / 2.0) / (img->zoom * WIDTH) + img->offsetx;
			z.y = (y - HEIGHT / 2.0) / (img->zoom * HEIGHT) + img->offsety;
			iter = mandelbrot(z, img);
			color_fractal(img, iter);
			my_pixel_put(x, y, img);
			x++;
		}
		y++;
	}
}

void	draw_julia(t_image *img)
{
	t_complex	z;
	int			x;
	int			y;
	int			iter;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z.x = (x - WIDTH / 2.0) / (img->zoom * WIDTH) + img->offsetx;
			z.y = (y - HEIGHT / 2.0) / (img->zoom * HEIGHT) + img->offsety;
			iter = julia(z, img);
			color_fractal(img, iter);
			my_pixel_put(x, y, img);
			x++;
		}
		y++;
	}
}

void	draw_burn(t_image *img)
{
	t_complex	z;
	int			x;
	int			y;
	int			iter;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			z.x = 1.5 * (x - WIDTH / 2.0) / (img->zoom * WIDTH) + img->offsetx;
			z.y = (y - HEIGHT / 2.0) / (img->zoom * HEIGHT) + img->offsety;
			iter = burning_ship(z, img);
			color_fractal(img, iter);
			my_pixel_put(x, y, img);
			y++;
		}
		x++;
	}
}
