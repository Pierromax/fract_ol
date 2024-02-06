/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:35:09 by ple-guya          #+#    #+#             */
/*   Updated: 2024/02/06 19:06:20 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_pixel_put(int x, int y, t_image *img)
{
	int	pixel_pos;

	pixel_pos = (x * img->bpp / 8) + (y * img->sl);
	img->data[pixel_pos] = img->color & 0xFF;
	img->data[pixel_pos + 1] = (img->color >> 8) & 0xFF;
	img->data[pixel_pos + 2] = (img->color >> 16) & 0xFF;
	img->data[pixel_pos + 3] = 0xFF;
}

void	color_fractal(t_image *img, int iter)
{
	if (iter == img->max_iter)
		img->color = rgb(0, 0, 0);
	else
	{
		img->color = rgb(0, 0, 255) + (iter * 255 / img->max_iter);
		img->color *= img->zoom;
	}
}

void	explore_julia(t_image *img, int key)
{
	if (key == 'j')
		img->jul_x += 0.01;
	if (key == 'h')
		img->jul_x -= 0.01;
	if (key == 'l')
		img->jul_y += 0.01;
	if (key == 'k')
		img->jul_y -= 0.01;
}

void	change_fractal(t_image *img, int key)
{
	if (key == 'b')
		img->fractal[0] = 'M';
	if (key == 'n')
		img->fractal[0] = 'J';
	if (key == 'm')
		img->fractal[0] = 'B';
	fill_image(img);
}
