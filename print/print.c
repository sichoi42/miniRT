#include "print.h"

void	ft_mlx_pixel_put(t_scene *scene, t_color3 *pixel_color, int x, int y)
{
	int		pixel;
	int		r;
	int		g;
	int		b;
	t_image	*img;

	img = &scene->mlx->img;
	pixel = img->bits_per_pixel / 8;
	r = (int)(255.999 * sqrt(pixel_color->x));
	g = (int)(255.999 * sqrt(pixel_color->y));
	b = (int)(255.999 * sqrt(pixel_color->z));
	img->addr[(x * pixel) + (y * img->line_length) + 2] = r;
	img->addr[(x * pixel) + (y * img->line_length) + 1] = g;
	img->addr[(x * pixel) + (y * img->line_length)] = b;
}
