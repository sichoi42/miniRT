#include "minirt.h"

void	input_check(int argc, char *argv[])
{
	int		len;

	if (argc != 2)
		print_error("Not correct argument\n");
	len = ft_strlen(argv[1]);
	if (ft_strcmp(".rt", argv[1] + len - 3) != 0)
		print_error("Need .rt file\n");
}

int	file_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error(NULL);
	return (fd);
}

void	pass_space(int fd, char *buf, char *space)
{
	int	size;
	int	i;

	size = ft_read(fd, buf, 1);
	while (size == 1)
	{
		i = -1;
		while (space[++i] != '\0')
		{
			if (*buf == space[i])
			{
				size = ft_read(fd, buf, 1);
				break ;
			}
		}
		if (space[i] == '\0')
			return ;
	}
	if (size == 0)
		*buf = '\0';
}

void	check_str(char *str)
{
	int dot;

	dot = 0;
	if (*str == '+' || *str == '-' || *str == '.')
	{
		++str;
		if (*str == '\0' || *str == '.')
			print_error("Wrong input\n");
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			++str;
		else if (*str == '.')
		{
			if (dot == 0)
				dot = 1;
			else
				print_error("Wrong input\n");
			++str;
		}
		else
			print_error("Wrong input\n");
	}
}

char	*read_to_str(int fd, char *buf)
{
	char	*str;
	int		size;
	int		i;
	int		capa;

	pass_space(fd, buf, " ,");
	capa = STR_SIZE;
	str = malloc_array(sizeof(char), capa);
	i = 0;
	str[i++] = *buf;
	size = ft_read(fd, buf, 1);
	while (size == 1 && *buf != ' ' && *buf != ',' && *buf != '\n')
	{
		if (i == capa - 1)
		{
			str = ft_realloc(str, capa, capa * 2);
			capa *= 2;
		}
		str[i++] = *buf;
		size = ft_read(fd, buf, 1);
	}
	str[i] = '\0';
	check_str(str);
	return (str);
}

double	make_float(int fd, char *buf)
{
	long long	num;
	long long	decimal;
	char		*str;
	double		result;

	str = read_to_str(fd, buf);
	num = stof_front(str);
	decimal = stof_behind(str);
	result = decimal;
	while (result >= 1.0)
		result /= 10.0;
	if (*str == '-')
		result *= -1;
	result += num;
	free(str);
	return (result);
}

double	input_ratio(int fd, char *buf)
{
	double	num;

	num = make_float(fd, buf);
	if (num < 0.0 || num > 1.0)
		print_error("Wrong input\n");
	return (num);
}

void	input_rgb(int fd, t_rgb *rgb, char *buf)
{
	char	*str;

	str = read_to_str(fd, buf);
	rgb->r = (unsigned char)stoi_rgb(str);
	free(str);
	str = read_to_str(fd, buf);
	rgb->g = (unsigned char)stoi_rgb(str);
	free(str);
	str = read_to_str(fd, buf);
	rgb->b = (unsigned char)stoi_rgb(str);
	free(str);
}

void	input_ambient(int fd, t_in_object *obj)
{
	char	buf;

	if (obj->a == NULL)
		obj->a = malloc_array(sizeof(t_in_ambient), 1);
	else
		print_error("Wrong input\n");
		//obj->a = ft_realloc(obj->a, obj->a_size, obj->a_size + 1);
		//++(obj->a_size);
/*
	str = read_to_str(fd, &buf);
	num = stof_front(str);
//	if (num != 0 && num != 1)
//		print_error("Wrong input\n");
	decimal = stof_behind(str);
	
	obj->a->ratio = input_ratio(num, decimal, str);
//	if (buf != ' ')
//		print_error("Wrong input\n");
*/
	obj->a->ratio = input_ratio(fd, &buf);
	input_rgb(fd, &(obj->a->rgb), &buf);
	/* ======================== test =============================== */
	printf("%f ", obj->a->ratio); fflush(0);
	printf("%d,%d,%d\n", obj->a->rgb.r, obj->a->rgb.g, obj->a->rgb.b); fflush(0);
	/* ======================================================= */
}

void	input_xyz(int fd, t_point3 *org, char *buf)
{
	org->x = make_float(fd, buf);
	org->y = make_float(fd, buf);
	org->z = make_float(fd, buf);
}

void	input_vec(int fd, t_vec3 *vec, char *buf)
{
	vec->x = make_float(fd, buf);
	if (vec->x < -1.0 || vec->x > 1.0)
		print_error("Wrong input\n");
	vec->y = make_float(fd, buf);
	if (vec->y < -1.0 || vec->y > 1.0)
		print_error("Wrong input\n");
	vec->z = make_float(fd, buf);
	if (vec->z < -1.0 || vec->z > 1.0)
		print_error("Wrong input\n");
}

void	input_camera(int fd, t_in_object *obj)
{
	char	buf;

	if (obj->c == NULL)
		obj->c = malloc_array(sizeof(t_in_camera), 1);
	else
		print_error("Wrong input\n");
	input_xyz(fd, &(obj->c->org), &buf);
	input_vec(fd, &(obj->c->org_vec), &buf);
	obj->c->fov = make_float(fd, &buf);
	if (obj->c->fov < 0 || obj->c->fov > 180)
		print_error("Wrong input\n");
	/* ======================== test =============================== */
	printf("%f,%f,%f\n", obj->c->org.x, obj->c->org.y, obj->c->org.z); fflush(0);
	printf("%f,%f,%f\n", obj->c->org_vec.x, obj->c->org_vec.y, obj->c->org_vec.z); fflush(0);
	printf("%f\n", obj->c->fov); fflush(0);
	/* ======================================================= */
}

void	input_light(int fd, t_in_object *obj)
{
	char	buf;

	if (obj->l == NULL)
		obj->l = malloc_array(sizeof(t_in_light), ++(obj->l_size));
	else
		obj->l = ft_realloc(obj->l, sizeof(t_in_light),
				sizeof(t_in_light) * (++(obj->l_size)));
	//input_xyz(fd, &(obj->l->org), &buf);
	input_xyz(fd, &((obj->l)[obj->l_size - 1].org), &buf);
	//obj->l->ratio = input_ratio(fd, &buf);
	(obj->l)[obj->l_size - 1].ratio = input_ratio(fd, &buf);
	//input_rgb(fd, &(obj->l->rgb), &buf);
	input_rgb(fd, &((obj->l)[obj->l_size - 1].rgb), &buf);
	/* ======================== test =============================== */
	printf("%f,%f,%f\n", (obj->l)[obj->l_size - 1].org.x, obj->l[obj->l_size - 1].org.y, obj->l[obj->l_size - 1].org.z); fflush(0);
	printf("%f\n", obj->l[obj->l_size - 1].ratio); fflush(0);
	printf("%d,%d,%d\n", obj->l[obj->l_size - 1].rgb.r, obj->l[obj->l_size - 1].rgb.g, obj->l[obj->l_size - 1].rgb.b); fflush(0);
	/* ======================================================= */
}

void	input_sphere(int fd, t_in_object *obj, char *buf)
{
	pass_space(fd, buf, " ");
	if (*buf != 'p')
		print_error("Wrong input\n");
	if (obj->sp == NULL)
		obj->sp = malloc_array(sizeof(t_in_sphere), ++(obj->sp_size));
	else
		obj->sp = ft_realloc(obj->sp, sizeof(t_in_sphere),
				sizeof(t_in_sphere) * (++(obj->sp_size)));
	//input_xyz(fd, &(obj->l->org), &buf);
	input_xyz(fd, &((obj->sp)[obj->sp_size - 1].org), buf);
	//obj->l->ratio = input_ratio(fd, &buf);
	(obj->sp)[obj->sp_size - 1].r = make_float(fd, buf);
	//input_rgb(fd, &(obj->l->rgb), &buf);
	input_rgb(fd, &((obj->sp)[obj->sp_size - 1].rgb), buf);
	/* ======================== test =============================== */
	printf("sp:%f,%f,%f\n", (obj->sp)[obj->sp_size - 1].org.x, obj->sp[obj->sp_size - 1].org.y, obj->sp[obj->sp_size - 1].org.z); fflush(0);
	printf("sp:%f\n", obj->sp[obj->sp_size - 1].r); fflush(0);
	printf("sp:%d,%d,%d\n", obj->sp[obj->sp_size - 1].rgb.r, obj->sp[obj->sp_size - 1].rgb.g, obj->sp[obj->sp_size - 1].rgb.b); fflush(0);
	/* ======================================================= */
}

void	input_plane(int fd, t_in_object *obj, char *buf)
{
	pass_space(fd, buf, " ");
	if (*buf != 'l')
		print_error("Wrong input\n");
	if (obj->pl == NULL)
		obj->pl = malloc_array(sizeof(t_in_plane), ++(obj->pl_size));
	else
		obj->pl = ft_realloc(obj->pl, sizeof(t_in_plane),
				sizeof(t_in_plane) * (++(obj->pl_size)));
	//input_xyz(fd, &(obj->l->org), &buf);
	input_xyz(fd, &((obj->pl)[obj->pl_size - 1].org), buf);
	//obj->l->ratio = input_ratio(fd, &buf);
	input_vec(fd, &((obj->pl)[obj->pl_size - 1].org_vec), buf);
	//input_rgb(fd, &(obj->l->rgb), &buf);
	input_rgb(fd, &((obj->pl)[obj->pl_size - 1].rgb), buf);
	/* ======================== test =============================== */
	printf("pl:%f,%f,%f\n", (obj->pl)[obj->pl_size - 1].org.x, obj->pl[obj->pl_size - 1].org.y, obj->pl[obj->pl_size - 1].org.z); fflush(0);
	printf("pl:%f,%f,%f\n", (obj->pl)[obj->pl_size - 1].org_vec.x, obj->pl[obj->pl_size - 1].org_vec.y, obj->pl[obj->pl_size - 1].org_vec.z); fflush(0);
	printf("pl:%d,%d,%d\n", obj->pl[obj->pl_size - 1].rgb.r, obj->pl[obj->pl_size - 1].rgb.g, obj->pl[obj->pl_size - 1].rgb.b); fflush(0);
	/* ======================================================= */
}

void	input_cylinder(int fd, t_in_object *obj, char *buf)
{
	pass_space(fd, buf, " ");
	if (*buf != 'y')
		print_error("Wrong input\n");
	if (obj->cy == NULL)
		obj->cy = malloc_array(sizeof(t_in_cylinder), ++(obj->cy_size));
	else
		obj->cy = ft_realloc(obj->cy, sizeof(t_in_cylinder),
				sizeof(t_in_cylinder) * (++(obj->cy_size)));
	//input_xyz(fd, &(obj->l->org), &buf);
	input_xyz(fd, &((obj->cy)[obj->cy_size - 1].org), buf);
	//obj->l->ratio = input_ratio(fd, &buf);
	input_vec(fd, &((obj->cy)[obj->cy_size - 1].org_vec), buf);
	obj->cy[obj->cy_size - 1].r = make_float(fd, buf);
	obj->cy[obj->cy_size - 1].h = make_float(fd, buf);
	//input_rgb(fd, &(obj->l->rgb), &buf);
	input_rgb(fd, &((obj->cy)[obj->cy_size - 1].rgb), buf);
	/* ======================== test =============================== */
	printf("cy:%f,%f,%f\n", (obj->cy)[obj->cy_size - 1].org.x, obj->cy[obj->cy_size - 1].org.y, obj->cy[obj->cy_size - 1].org.z); fflush(0);
	printf("cy:%f,%f,%f\n", (obj->cy)[obj->cy_size - 1].org_vec.x, obj->cy[obj->cy_size - 1].org_vec.y, obj->cy[obj->cy_size - 1].org_vec.z); fflush(0);
	printf("cy:%f,%f\n", (obj->cy)[obj->cy_size - 1].r, obj->cy[obj->cy_size - 1].h); fflush(0);
	printf("cy:%d,%d,%d\n", obj->cy[obj->cy_size - 1].rgb.r, obj->cy[obj->cy_size - 1].rgb.g, obj->cy[obj->cy_size - 1].rgb.b); fflush(0);
	/* ======================================================= */
}

void	init_input_obj(int fd, t_in_object *obj)
{
	char	buf;

	ft_memset(obj, sizeof(t_in_object), 0);
	while (1)
	{
		pass_space(fd, &buf, " \n");
		if (buf == 'A')
			input_ambient(fd, obj);
		else if (buf == 'C')
			input_camera(fd, obj);
		else if (buf == 'L')
			input_light(fd, obj);
		else if (buf == 's')
			input_sphere(fd, obj, &buf);
		else if (buf == 'p')
			input_plane(fd, obj, &buf);
		else if (buf == 'c')
			input_cylinder(fd, obj, &buf);
		else if (buf == '\0')
			break ;
		else
			print_error("Wrong input\n");
	}
}

int	main(int argc, char *argv[])
{
	int	fd;
	t_in_object	in_obj;

	input_check(argc, argv);
	fd = file_open(argv[1]);
	init_input_obj(fd, &in_obj);
	close(fd);
	return (0);
}
