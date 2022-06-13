#ifndef PARSING_H
# define PARSING_H

/* printf, perror */
# include <stdio.h>
/* open */
# include <fcntl.h>
/* close, read, write,  */
# include <unistd.h>
/* malloc, free, exit */
# include <stdlib.h>
/* strerror */
# include <string.h>
# include <math.h>
# include "structures.h"

# define OVER_LONG_NUM 9223372036854775808UL
# define OVER_INT_NUM 2147483648
# define MAX_PRECISION 1000000000UL
# define STR_SIZE 512;

typedef struct s_in_window {
	int	width;
	int	height;
}	t_in_window;

typedef struct s_in_ambient {
	double		ratio;/* [0.0, 1.0] */
	t_color3	rgb;/*[0-255] */
}	t_in_ambient;

typedef struct s_in_camera {
	t_point3	org;
	t_vec3		org_vec;/*[-1,1]*/
	double		fov;/*[0, 180]*/
}	t_in_camera;

typedef struct s_in_light {
	t_point3	org;
	double		ratio;/*[0.0, 1.0]*/
	t_color3	rgb;/*[0-255]*/
}	t_in_light;

typedef struct s_in_sphere {
	t_point3	org;
	double		r;
	t_color3	rgb;/*[0-255]*/
}	t_in_sphere;

typedef struct s_in_plane {
	t_point3	org;
	t_vec3		org_vec;/*[-1,1]*/
	t_color3	rgb;/*[0-255]*/
}	t_in_plane;

typedef struct s_in_cylinder {
	t_point3	org;
	t_vec3		org_vec;/*[-1,1]*/
	double		r;
	double		h;
	t_color3	rgb;/*[0,255]*/
}	t_in_cylinder;

typedef struct s_in_cone {
	t_point3	org;
	t_vec3		org_vec;/*[-1,1]*/
	double		h;
	double		a;/*(0, 90)*/
	t_color3	rgb;
}	t_in_cone;

typedef struct s_in_object {
	t_in_window		*w;
	t_in_ambient	*a;
	t_in_camera		*c;
	t_in_light		*l;
	t_in_sphere		*sp;
	t_in_plane		*pl;
	t_in_cylinder	*cy;
	t_in_cone		*co;
	int				l_size;
	int				sp_size;
	int				pl_size;
	int				cy_size;
	int				co_size;
}	t_in_object;

/* base */
void				ft_memset(void *target, unsigned int size, int input);
void				print_error(char *message);
int					ft_strlen(char *s);
int					ft_strcmp(char *l, char *r);
void				*malloc_array(int size, int len);
void				*ft_realloc(void *ptr, int ptr_size, int new_size);
int					ft_read(int fd, char *buf, int size);
unsigned long long	stof_front(char *str);
unsigned long long	stof_behind(char *str);
int					stoi_rgb(char *str);
int					ft_stoi(char *str);

#endif
