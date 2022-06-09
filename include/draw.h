#ifndef DRAW_H
# define DRAW_H

# include "structures.h"
# include "parsing.h"

t_obj	*adding_objects(t_in_object *in_obj, t_obj **light);
t_scene	*scene_init(t_scene *scene, t_in_object *in_obj);
void	init_mlx(t_mlx *mlx, t_scene *scene);
void	draw(t_in_object *in_obj);

#endif
