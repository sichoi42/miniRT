#ifndef PRINT_H
# define PRINT_H

# include <stdio.h>
# include <math.h>
# include "structures.h"
# include "mlx.h"

int		color3_to_pixel(t_color3 color);
void	ft_mlx_pixel_put(t_scene *scene, t_color3 *pixel_color, int x, int y);
// void	ft_mlx_pixel_put(t_scene *scene, int color, int x, int y);

#endif
