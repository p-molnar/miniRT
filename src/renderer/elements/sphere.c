/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:58:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/09 14:46:44 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>


long double	get_sphere_intersections(t_ray *ray, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;
	t_vec3		*CO;
	long double	smallest;

	CO = create_dir_vec(obj->pos, *ray->origin);
	quad_param[0] = dot(ray->dir, ray->dir);
	quad_param[1] = 2.0 * dot(CO, ray->dir);
	quad_param[2] = dot(CO, CO) - pow(obj->diameter / 2, 2);
	t = quad_eq_solver(quad_param[0], quad_param[1], quad_param[2], &d);
	free(CO);
	if (d < 0)
		return (-1); // new!
	if (t[0] < t[0])
		smallest = t[0];
	else
		smallest = t[1];
	free(t);
	return (smallest);
}
