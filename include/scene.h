#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"
# include "parsing.h"

// canvas.c, camera.c
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_in_camera *in_cam);

// object_create.c
t_obj		*object(t_obj_type type, void *element, t_color3 albedo);
t_sphere	*sphere(t_in_sphere *in_sp, void *mlx_ptr);
t_plane		*plane(t_in_plane *in_pl, void *mlx_ptr);
t_cylinder	*cylinder(t_in_cylinder *in_cl, void *mlx_ptr);
t_cone		*cone(t_in_cone *in_co, void *mlx_ptr);
t_light		*point_light(t_in_light *in_light);

#endif
