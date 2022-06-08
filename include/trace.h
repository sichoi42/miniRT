#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

// -----in ray folder-----

//ray.c
t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);

// phong_ligting.c
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_bool		in_shadow(t_obj *obj, t_ray light_ray, double light_len);
t_color3	get_point_light(t_scene *scene, t_light *light);
t_color3	phong_lighting(t_scene *scene);

// -----in hit folder-----

// hit.c
t_bool		hit(t_obj *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_obj *obj, t_ray *ray, t_hit_record *rec);

// hit_sphere.c
t_bool		hit_sphere(t_obj *obj, t_ray *ray, t_hit_record *rec);

// hit_plane.c
t_bool		hit_plane(t_obj *obj, t_ray *ray, t_hit_record *rec);

// normal.c
void		set_face_normal(t_ray *ray, t_hit_record *rec);

#endif
