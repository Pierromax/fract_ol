/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:57:24 by ple-guya          #+#    #+#             */
/*   Updated: 2024/02/05 02:36:22 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init(t_image *img)
{
	img->zoom = 0.4;
	img->offsetx = -0.5;
	img->offsety = 0.0;
	img->max_iter = 30;
	img->color = rgb(0, 0, 255);
	img->mlx_ptr = mlx_init();
	if (!(img->mlx_ptr))
		quit(img);
	img->win_ptr = mlx_new_window(img->mlx_ptr, WIDTH, HEIGHT, img->fractal);
	if (!(img->win_ptr))
		quit(img);
	img->img_ptr = mlx_new_image(img->mlx_ptr, WIDTH, HEIGHT);
	if (!(img->img_ptr))
		quit(img);
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->sl, &img->e);
}

void	event_hook(t_image *img)
{
	mlx_key_hook(img->win_ptr, deal_key, img);
	mlx_mouse_hook(img->win_ptr, mickey, img);
	mlx_hook(img->win_ptr, 17, (1L << 17), quit, img);
}

void	reset(t_image *img)
{
	img->zoom = 0.4;
	img->offsetx = -0.5;
	img->offsety = 0.0;
	img->max_iter = 30;
}

int	choose_ur_fractal(int ac, char **av, t_image *img)
{
	if ((ac == 2 && av[1][0] == 'M')
		|| (ac == 2 && av[1][0] == 'B')
		|| (ac == 4 && av[1][0] == 'J'))
	{
		img->fractal = av[1];
		if (img->fractal[0] == 'J')
		{
			img->jul_x = ft_atof(av[2]);
			img->jul_y = ft_atof(av[3]);
		}
		return (1);
	}
	else
	{
		ft_printf("%s", "please chose ur fractal : \
			\n- Mandelbrot\n- Julia <real> <imaginary>\n- Burning_ship");
		free(img);
		return (0);
	}
}

int	main(int ac, char **av)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (img == 0)
		return (0);
	if (choose_ur_fractal(ac, av, img) == 0)
		return (0);
	init(img);
	event_hook(img);
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	mlx_do_sync(img->mlx_ptr);
	mlx_loop(img->mlx_ptr);
	mlx_destroy_display(img->mlx_ptr);
	free(img);
	return (0);
}
