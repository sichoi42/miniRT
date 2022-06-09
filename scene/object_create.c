#include "structures.h"
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

t_cylinder	*cylinder(t_point3 p, t_vec3 normal, double radius, double height)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		exit(1);
	cy->p = p;
	cy->normal = normal;
	cy->radius = radius;
	cy->height = height;
	return (cy);
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
