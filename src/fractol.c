/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:44:57 by ple-guya          #+#    #+#             */
/*   Updated: 2023/12/16 01:25:51 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"

int deal_key(int key, void *param)
{
	write (1, "X", 1);
	return(0);
}


int main(void)
{
    void	*mlx_ptr;
    void	*win_ptr;
    void	*win_ptr2;
	int		i;
	int		j;

	i = 0;
	j = 0;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "My first window!");
	win_ptr2 = mlx_new_window(mlx_ptr, 250, 250, "My second window!");
	while(i < 500)
		mlx_pixel_put(mlx_ptr, win_ptr, i++, j, 0xFFFFFF);
	while  (j < 500)
		mlx_pixel_put(mlx_ptr, win_ptr, i, j++, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}

