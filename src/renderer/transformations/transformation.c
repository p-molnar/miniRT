/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transformation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 11:51:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:21:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

static t_mx	apply_origin_transformations(t_mx origin, t_scn_el *obj_info)
{
	t_mx	transformed_mx;
	t_mx	tmp;

	tmp = multiply_mx(obj_info->inv_translation, origin);
	transformed_mx = multiply_mx(obj_info->inv_rotation, tmp);
	return (transformed_mx);
}

static t_mx	apply_direction_transformations(t_mx dir, t_scn_el *obj_info)
{
	t_mx	transformed_mx;

	transformed_mx = multiply_mx(obj_info->inv_rotation, dir);
	return (transformed_mx);
}

t_ray	apply_transformations(t_ray ray, t_scn_el *obj_info)
{
	t_mx	origin_mx;
	t_mx	dir_mx;
	t_ray	transformed_ray;

	origin_mx = apply_origin_transformations(coord_to_mx(ray.origin, 4, 1, 1),
			obj_info);
	transformed_ray.origin = create_coord(origin_mx.m[0], origin_mx.m[1],
			origin_mx.m[2]);
	dir_mx = apply_direction_transformations(coord_to_mx(ray.dir.dir, 4, 1, 1),
			obj_info);
	transformed_ray.dir = create_vec(dir_mx.m[0], dir_mx.m[1], dir_mx.m[2]);
	return (transformed_ray);
}
