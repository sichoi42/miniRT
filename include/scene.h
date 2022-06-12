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
t_sphere	*sphere(t_point3 center, double radius);
t_plane		*plane(t_point3 p, t_vec3 normal);
t_cylinder	*cylinder(t_point3 p, t_point3 n, double radius, double height);
t_cone		*cone(t_point3 p, t_vec3 n, double degree, double h);
t_light		*point_light(t_point3 orig, t_color3 color, double ratio);

#endif
