#ifndef STRUCTURES_H
# define STRUCTURES_H
# define TRUE 1
# define FALSE 0

# define SP 0
# define PL 1
# define POINT_LIGHT 2

# define EPSILON 1e-6
# define LUMEN 3 // 밝기 조절.

typedef int t_bool;
typedef int t_obj_type;

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;

struct s_vec3
{
	double x;
	double y;
	double z;
};

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

typedef	struct s_camera
{
	t_point3	orig; // 카메라의 위치(원점)
	double		viewport_h; // viewport의 세로길이
	double		viewport_w; // viewport의 가로길이
	t_vec3		horizontal; // 수평길이 Vector
	t_vec3		vertical; // 수직길이 Vector
	double		focal_len;
	t_point3	left_bottom;
}	t_camera;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio; // 종횡비
}	t_canvas;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
}	t_sphere;

typedef struct s_plane
{
	t_point3	p;
	t_vec3		normal;
}	t_plane;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t_min;
	double		t_max;
	double		t;
	t_bool		front_face;
	t_color3	albedo;
}	t_hit_record;

typedef struct s_obj
{
	t_obj_type		type;
	void			*element;
	t_color3		albedo;
	struct s_obj	*next;
}	t_obj;

typedef struct s_light
{
	t_point3	orig;
	t_color3	light_color;
	double		bright_ratio;
}	t_light;

typedef struct s_scene
{
	t_mlx			*mlx;
	t_canvas		canvas;
	t_camera		camera;
	t_obj			*objs;
	t_obj			*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;

#endif
