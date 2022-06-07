#include "print.h"

void	ft_mlx_pixel_put(t_scene *scene, t_color3 *pixel_color, int x, int y)
{
	int		pixel;
	int		r;
	int		g;
	int		b;
	t_image	*image;

	image = scene->mlx.image;
	pixel = image->bits_per_pixel / 8;
	r = (int)(255.999 * sqrt(pixel_color->x));
	g = (int)(255.999 * sqrt(pixel_color->y));
	b = (int)(255.999 * sqrt(pixel_color->z));
	if ((x >= 0 || x <= scene->canvas.width) && (y >= 0 || y <= scene->canvas.height))
	{
		image->addr[(x * pixel) + (y * image->line_length) + 2] = r;
		image->addr[(x * pixel) + (y * image->line_length) + 1] = g;
		image->addr[(x * pixel) + (y * image->line_length)] = b;
	}
}
