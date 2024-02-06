/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:10:12 by ple-guya          #+#    #+#             */
/*   Updated: 2024/02/05 00:03:17 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mickey(int mouse, int x, int y, t_image *img)
{
	if (mouse == 4)
		zoom(x, y, img);
	else if (mouse == 5)
		dezoom(x, y, img);
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int	quit(t_image *img)
{
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	free(img);
	exit(0);
	return (0);
}

int	deal_key(int key, t_image *img)
{
	if (key == 65307)
		quit(img);
	if (key == 65361)
		img->offsetx -= 0.1 / img->zoom;
	if (key == 65363)
		img->offsetx += 0.1 / img->zoom;
	if (key == 65362)
		img->offsety -= 0.1 / img->zoom;
	if (key == 65364)
		img->offsety += 0.1 / img->zoom;
	if (key == 'p')
		img->max_iter += 40;
	if (key == 'o')
		img->max_iter -= 40;
	if (key == 114)
		reset(img);
	change_fractal(img, key);
	explore_julia(img, key);
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

void	zoom(int x, int y, t_image *img)
{
	img->zoom *= 1.1;
	img->offsetx += (x - WIDTH / 2.0) / (4 * img->zoom * WIDTH);
	img->offsety += (y - HEIGHT / 2.0) / (4 * img->zoom * HEIGHT);
	if (img->max_iter < MAX_ITER / 4)
		img->max_iter += img->zoom / img->max_iter;
	if (img->max_iter > MAX_ITER / 4 && img->max_iter < MAX_ITER / 2)
		img->max_iter += (img->zoom / 100) / img->max_iter;
	if (img->max_iter > MAX_ITER / 2 && img->max_iter < ((MAX_ITER * 3) / 4))
		img->max_iter += (img->zoom / 1000) / img->max_iter;
	if (img->max_iter > ((MAX_ITER * 3) / 4) && img->max_iter < MAX_ITER)
		img->max_iter += (img->zoom / 10000) / img->max_iter;
}

void	dezoom(int x, int y, t_image *img)
{
	img->zoom *= 0.9;
	img->offsetx += (x - WIDTH / 2.0) / (4 * img->zoom * WIDTH);
	img->offsety += (y - HEIGHT / 2.0) / (4 * img->zoom * HEIGHT);
	if (img->max_iter < MAX_ITER / 4)
		img->max_iter -= img->zoom / img->max_iter;
	if (img->max_iter > MAX_ITER / 4 && img->max_iter < MAX_ITER / 2)
		img->max_iter -= (img->zoom / 100) / img->max_iter;
	if (img->max_iter > MAX_ITER / 2 && img->max_iter < ((MAX_ITER * 3) / 4))
		img->max_iter -= (img->zoom / 1000) / img->max_iter;
	if (img->max_iter > ((MAX_ITER * 3) / 4) && img->max_iter < MAX_ITER)
		img->max_iter -= (img->zoom / 10000) / img->max_iter;
}
