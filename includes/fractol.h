/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:06:54 by ple-guya          #+#    #+#             */
/*   Updated: 2024/02/04 21:34:49 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"
# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITER 1000

typedef struct s_image
{
	double	zoom;
	double	offsetx;
	double	offsety;
	double	real;
	double	imag;
	void	*img_ptr;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*data;
	int		sl;
	int		bpp;
	int		e;
	int		max_iter;
	int		color;
	char	*fractal;
	double	jul_x;
	double	jul_y;
}	t_image;

typedef struct s_complex
{
	double	x;
	double	y;
}	t_complex;

//fractal
int		mandelbrot(t_complex pos, t_image *img);
int		julia( t_complex z, t_image *img);
int		burning_ship(t_complex z, t_image *img);
//handle t_image
void	fill_image(t_image *img);
int		rgb(int r, int g, int b);
void	draw_mandelbrot(t_image *img);
void	draw_julia(t_image *img);
void	draw_burn(t_image *img);
void	color_fractal(t_image *img, int iter);
// events
void	zoom(int x, int y, t_image *img);
void	dezoom(int x, int y, t_image *img);
int		mickey(int mouse, int x, int y, t_image *img);
int		deal_key(int key, t_image *img);
int		quit(t_image *img);
void	reset(t_image *img);
void	event_hook(t_image *img);
void	my_pixel_put(int x, int y, t_image *img);
void	explore_julia(t_image *img, int key);
void	change_fractal( t_image *img, int key);

#endif