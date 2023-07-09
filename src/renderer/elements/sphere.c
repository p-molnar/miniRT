/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:58:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/08 15:21:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>


long double	get_sphere_intersections(t_ray *ray, t_scn_el *obj)
{
	t_quad_param param;
	long double	d;
	long double	*t;
	t_vec3		*obj_to_com;
	long double	smallest;

	obj_to_com = create_dir_vec(obj->pos, *ray->origin);
	param.a = dot(ray->dir, ray->dir);
	param.b = 2.0 * dot(obj_to_com, ray->dir);
	param.c = dot(obj_to_com, obj_to_com) - pow(obj->diameter / 2, 2);
	free(obj_to_com);
	t = quad_eq_solver(param, &d);
	smallest = -1;
	if (d >= 0)
	{
		if (t[0] <= t[1])
			smallest = t[0];
		else
			smallest = t[1];
	}
	free(t);
	return (smallest);
}
