/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 12:21:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 21:07:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	update_hit_obj(t_hit_obj *hit_obj, t_hit_obj updated_val)
{
	hit_obj->attr = updated_val.attr;
	hit_obj->dist = updated_val.dist;
	hit_obj->inc_p_raw = updated_val.inc_p_raw;
	hit_obj->is_hit = updated_val.is_hit;
}

t_hit_obj	intersect(t_ray ray, t_scn_el **el, t_range range,
		enum e_isect mode)
{
	t_hit_obj	hit_obj;
	t_coord3	inc_p;
	long double	t;
	int			i;

	hit_obj = (t_hit_obj){.is_hit = false, .dist = INF, .attr = NULL};
	i = -1;
	while (el && el[++i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(ray, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(ray, el[i], &inc_p);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(ray, el[i]);
		if (is_in_range_f(t, range.min, range.max, "[]") && t < hit_obj.dist)
		{
			update_hit_obj(&hit_obj, (t_hit_obj){.attr = el[i], .dist = t,
				.inc_p_raw = inc_p, .is_hit = true});
			if (mode == SHADOW)
				return (hit_obj);
		}
	}
	return (hit_obj);
}
