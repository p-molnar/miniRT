/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:58:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:20:18 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

long double	get_sphere_intersections(t_ray ray, t_scn_el *obj)
{
	t_quad_param	param;
	long double		d;
	long double		*t;
	t_vec3			obj_to_cam;
	long double		smallest;

	obj_to_cam = create_dir_vec(obj->pos, ray.origin);
	param.a = dot(ray.dir, ray.dir);
	param.b = 2.0 * dot(obj_to_cam, ray.dir);
	param.c = dot(obj_to_cam, obj_to_cam) - pow(obj->diameter / 2, 2);
	t = quad_eq_solver(param, &d);
	smallest = -1;
	if (t && d >= 0)
		smallest = yield_smallest_positive(t, 2);
	if (t)
		free(t);
	return (smallest);
}
