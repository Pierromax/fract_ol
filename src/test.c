#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 1000
#define MAX_ITER 100

typedef struct 
{
    double zoom;
    double offsetX;
    double offsetY;
	double real;
	double imag;
    void *img_ptr;
	void *mlx_ptr;
	void *win_ptr;
    char *data;
    int size_line;
    int bpp;
    int endian;
} Image;

int mandelbrot(double x, double y)
{
	int i;
	double real = x;
	double imag = y;
	double temp;
	i = 0;

	while (i < MAX_ITER)
	{
		temp = real * real - imag * imag + x;
		imag = 2 * real * imag + y;
		real = temp;
		if (real * real + imag * imag > 8)
			return (i);
		i++;
	}
	return (i);
}

void fill_image(Image *img)
{
    int x, y;
    int color;

	y = 0;
    while (y < HEIGHT)
    {
		x = 0;
        while (x < WIDTH)
        {
            double zx = (x - WIDTH / 2.0) / (img->zoom * WIDTH) + img->offsetX;
            double zy = (y - HEIGHT / 2.0) / (img->zoom * HEIGHT) + img->offsetY;

            int value = mandelbrot(zx, zy);
            color = value *255/ MAX_ITER;

            // Calculate the pixel x = 653 y = 514position in the image
            int pixel_pos = (x * img->bpp / 8) + (y * img->size_line);

            // Set the color in the image data
            img->data[pixel_pos] = color ;                // Blue channel
            img->data[pixel_pos + 1] = color ;            // Green channel
            img->data[pixel_pos + 2] = color ;            // Red channel
            img->data[pixel_pos + 3] = 0;                // Alpha channel (set to 0 for fully opaque)
			x++;
        }
		y++;
    }
}

void zoom(int x, int y, Image *img)
{
	img->zoom *= 1.1;
	double mouseX = (double)x / img->zoom + img->offsetX;
    double mouseY = (double)y / img->zoom + img->offsetY;
    img->offsetX = mouseX - (double)x / img->zoom;
    img->offsetY = mouseY - (double)y / img->zoom;
	// printf("x = %f y = %f\n", img->offsetX, img->offsetY);
}

void dezoom(int x, int y, Image *img)
{
	img->zoom /= 1.1;
	double mouseX = (double)x / img->zoom + img->offsetX;
    double mouseY = (double)y / img->zoom + img->offsetY;
    img->offsetX = mouseX - (double)x / img->zoom;
    img->offsetY = mouseY - (double)y / img->zoom;
	// printf("x = %f y = %f\n", img->offsetX, img->offsetY);
}

int mickey(int mouse, int x, int y, Image *img)
{
	if (mouse == 4)
		zoom(x, y, img);
    else if (mouse == 5)
		dezoom(x, y, img);	
	printf("x = %f y = %f\n", img->offsetX, img->offsetY);
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}

int quit()
{
	exit(0);
	return(0);
}

int deal_key(int key, Image *img)
{
    if (key == 65307)
        exit(0);
	else if (key == '=')
        img->zoom *= 1.1;
    else if (key == '-')
		img->zoom /= 1.1;
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
    return (0);
}

int main(void)
{
	Image *img;

	img = malloc(sizeof(Image));
	if(img == NULL)
        return 1;
	img->zoom = 1.0;
    img->offsetX = 0.0;
    img->offsetY = 0.0;
    img->mlx_ptr = mlx_init();
    img->win_ptr = mlx_new_window(img->mlx_ptr, WIDTH, HEIGHT, "Mandelbrot Set");
	img->img_ptr = mlx_new_image(img->mlx_ptr, WIDTH, HEIGHT);
    img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
    mlx_key_hook(img->win_ptr, deal_key, img);
	mlx_mouse_hook(img->win_ptr, mickey, img);
	mlx_hook(img->win_ptr, 17, (1L << 17), &quit, img);
	fill_image(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	mlx_do_sync(img->mlx_ptr);
    mlx_loop(img->mlx_ptr);
	free(img);
    return (0);
}