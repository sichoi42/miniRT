#include "print.h"

void	ft_mlx_pixel_put(t_scene *scene, t_color3 *pixel_color, int x, int y)
{
	int		pixel;
	int		r;
	int		g;
	int		b;
	t_mlx	*mlx;

	mlx = scene->mlx;
	pixel = mlx->bits_per_pixel / 8;
	r = (int)(255.999 * sqrt(pixel_color->x));
	g = (int)(255.999 * sqrt(pixel_color->y));
	b = (int)(255.999 * sqrt(pixel_color->z));
	mlx->addr[(x * pixel) + (y * mlx->line_length) + 2] = r;
	mlx->addr[(x * pixel) + (y * mlx->line_length) + 1] = g;
	mlx->addr[(x * pixel) + (y * mlx->line_length)] = b;
}
