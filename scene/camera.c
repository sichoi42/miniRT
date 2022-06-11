#include "scene.h"
#include "parsing.h"

// t_camera	camera(t_canvas *canvas, t_point3 orig)
// {
// 	t_camera	cam;
// 	double		focal_len;
// 	double		viewport_height;

// 	viewport_height = 2.0;
// 	focal_len = 1.0;
// 	cam.orig = orig;
// 	cam.viewport_h = viewport_height;
// 	cam.viewport_w = viewport_height * canvas->aspect_ratio;
// 	cam.focal_len = focal_len;
// 	cam.horizontal = vec3(cam.viewport_w, 0, 0);
// 	cam.vertical = vec3(0, cam.viewport_h, 0);
// 	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
// 	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)),
// 								vdivide(cam.vertical, 2)), vec3(0, 0, focal_len));
// 	return (cam);
// }

t_camera	camera(t_canvas *canvas, t_in_camera *in_cam)
{
	t_camera	cam;
	// double		focal_len;
	double		viewport_height;
	t_vec3		v_up;
	double		theta;
	double		h;

	v_up = vec3(0, 1, 0);
	theta = degree_to_radian(in_cam->fov);
	h = tan(theta / 2.0);
	viewport_height = 2.0 * h;
	// focal_len = 1.0;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.orig = in_cam->org;
	cam.dir = in_cam->org_vec;
	cam.w = vunit(vmult(cam.dir, -1));
	cam.u = vunit(vcross(v_up, cam.w));
	cam.v = vcross(cam.w, cam.u);
	// cam.focal_len = focal_len;
	cam.horizontal = vmult(cam.u, cam.viewport_w);
	cam.vertical = vmult(cam.v, cam.viewport_h);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), cam.w);
	return (cam);
}