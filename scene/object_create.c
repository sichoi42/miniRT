#include "structures.h"
#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

t_obj	*object(t_obj_type type, void *element, t_color3 albedo)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (new == NULL)
		exit(1);
	new->type = type;
	new->element = element;
	new->albedo = albedo;
	new->next = NULL;
	return (new);
}

t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		exit(1);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_plane	*plane(t_point3 p, t_vec3 normal)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		exit(1);
	pl->p = p;
	pl->normal = normal;
	return (pl);
}

t_cylinder	*cylinder(t_point3 p, t_point3 n, double radius, double height)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		exit(1);
	cy->p = p;
	cy->normal = n;
	cy->radius = radius;
	cy->height = height;
	cy->tc = vplus(p, vmult(cy->normal, cy->height / 2));
	cy->bc = vplus(p, vmult(cy->normal, -(cy->height) / 2));
	return (cy);
}

t_cone	*cone(t_point3 p, t_vec3 n, double degree, double h)
{
	t_cone	*co;

	co = malloc(sizeof(t_cone));
	if (co == NULL)
		exit(1);
	co->a = degree_to_radian(degree);
	co->cos = cos(co->a);
	co->sin = sin(co->a);
	co->cos2 = co->cos * co->cos;
	co->sin2 = 1 - co->cos2;
	co->tan = co->sin / co->cos;
	co->tan2 = co->tan * co->tan;
	co->h = h;
	co->r = h * co->tan;
	co->p = p;
	co->n = n;
	co->flip_n = vflip(n);
	co->t = vplus(p, vmult(n, h));
	return (co);
}

t_light	*point_light(t_point3 orig, t_color3 color, double ratio)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		exit(1);
	light->orig = orig;
	light->light_color = color;
	light->bright_ratio = ratio;
	return (light);
}
