/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:58:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/05 20:53:19 by pmolnar       ########   odam.nl         */
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
	t_vec3		*CO;
	long double	smallest;

	CO = create_dir_vec(obj->pos, *ray->origin);
	param.a = dot(ray->dir, ray->dir);
	param.b = 2.0 * dot(CO, ray->dir);
	param.c = dot(CO, CO) - pow(obj->diameter / 2, 2);
	free(CO);
	t = quad_eq_solver(param, &d);
	if (d < 0)
		return (-1); // new!
	if (t[0] < t[0])
		smallest = t[0];
	else
		smallest = t[1];
	free(t);
	return (smallest);
}
