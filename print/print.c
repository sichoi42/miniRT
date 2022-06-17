#include "print.h"
#include "utils.h"

static int	color_calc(double rgb)
{
	return (clamp((int)(256 * rgb), 0, 255));
}

int	color3_to_pixel(t_color3 color)
{
	int	pixel;

	pixel = 0;
	pixel |= color_calc(color.x) << 16;
	pixel |= color_calc(color.y) << 8;
	pixel |= color_calc(color.z);
	return (pixel);
}

// void	ft_mlx_pixel_put(t_scene *scene, int color, int x, int y)
// {
// 	t_image	*img;
// 	char	*dst;

// 	img = &scene->mlx->img;
// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

void	ft_mlx_pixel_put(t_scene *scene, t_color3 *pixel_color, int x, int y)
{
	int		pixel;
	int		r;
	int		g;
	int		b;
	t_image	*img;

	// printf("%lf, %lf, %lf\n", pixel_color->x, pixel_color->y, pixel_color->z);
	img = &scene->mlx->img;
	pixel = img->bits_per_pixel / 8;
	r = (int)(255.999 * sqrt(pixel_color->x));
	g = (int)(255.999 * sqrt(pixel_color->y));
	b = (int)(255.999 * sqrt(pixel_color->z));
	img->addr[(x * pixel) + (y * img->line_length) + 2] = r;
	img->addr[(x * pixel) + (y * img->line_length) + 1] = g;
	img->addr[(x * pixel) + (y * img->line_length)] = b;
}
