#include "mlx.h"
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 100

typedef struct {
    double zoom;
    double offsetX;
    double offsetY;
    double offsetZ;
} FractalParams;

int mandelbrot(double x, double y, double z) {
    double zx = x;
    double zy = y;
    double zz = z;

    int iterations = 0;
    while (iterations < MAX_ITER) {
        double xtemp = zx * zx - zy * zy - zz * zz + x;
        double ytemp = 2.0 * zx * zy + y;
        double ztemp = 2.0 * zx * zz + z;

        zx = xtemp;
        zy = ytemp;
        zz = ztemp;

        if ((zx * zx + zy * zy + zz * zz) > 4.0)
            break;

        iterations++;
    }

    return iterations;
}

int deal_key(int key, void *param)
{
    FractalParams *fractalParams = (FractalParams *)param;

    if (key == 65307)
        exit(0);
    else if (key == '=')
        fractalParams->zoom *= 1.1;
    else if (key == '-')
        fractalParams->zoom /= 1.1;
    return (0);
}

void fill_image(void *img_ptr, char *data, int size_line, int bpp, FractalParams *fractalParams) {
    int x, y;
    int color;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            double zx = (x - WIDTH / 2.0) / (0.5 * fractalParams->zoom * WIDTH) + fractalParams->offsetX;
            double zy = (y - HEIGHT / 2.0) / (0.5 * fractalParams->zoom * HEIGHT) + fractalParams->offsetY;
            double zz = fractalParams->offsetZ;

            int value = mandelbrot(zx, zy, zz);
            color = value * 255 / MAX_ITER;

            // Calculate the pixel position in the image
            int pixel_pos = (x * bpp / 8) + (y * size_line);

            // Set the color in the image data
            data[pixel_pos] = color;            // Blue channel
            data[pixel_pos + 1] = color;        // Green channel
            data[pixel_pos + 2] = color;        // Red channel
            data[pixel_pos + 3] = 0;            // Alpha channel (set to 0 for fully opaque)
        }
    }
}

int main(void) {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int size_line;
    int bpp;

    FractalParams fractalParams;
    fractalParams.zoom = 1.0;
    fractalParams.offsetX = 0.0;
    fractalParams.offsetY = 0.0;
    fractalParams.offsetZ = 0.0;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "3D Mandelbrot Set");

    img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, NULL);

    mlx_key_hook(win_ptr, &deal_key, &fractalParams);

    fill_image(img_ptr, img_data, size_line, bpp, &fractalParams);
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_do_sync(mlx_ptr);
    mlx_loop(mlx_ptr);

    return 0;
}
