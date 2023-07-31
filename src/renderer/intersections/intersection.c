/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 12:21:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/31 12:22:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	update_hit_obj(t_hit_obj *hit_obj, t_scn_el *el, long double dist,
		bool is_hit)
{
	hit_obj->attr = el;
	hit_obj->dist = dist;
	hit_obj->is_hit = is_hit;
}

t_hit_obj	intersect(t_ray ray, t_scn_el **el, t_range range,
		enum e_isect mode)
{
	t_hit_obj	obj;
	long double	t;
	int			i;

	obj = (t_hit_obj){.is_hit = false, .dist = INF, .attr = NULL};
	i = 0;
	while (el && el[i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(ray, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(ray, el[i], &obj.inc_p_raw);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(ray, el[i]);
		if (is_in_range_f(t, range.min, range.max) && t < obj.dist)
		{
			update_hit_obj(&obj, el[i], t, true);
			if (mode == SHADOW)
				return (obj);
		}
		i++;
	}
	return (obj);
}