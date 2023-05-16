/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:58:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/16 14:18:48 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>


long double	get_sphere_intersections(long double start[3], t_vec3 *dir, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;
	t_vec3		*CO;
	long double	smallest;

	CO = create_vec(obj->coord, start);
	quad_param[0] = dot(dir, dir);
	quad_param[1] = 2.0 * dot(CO, dir);
	quad_param[2] = dot(CO, CO) - pow(obj->radius, 2);
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