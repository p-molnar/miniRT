/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/28 20:40:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

long double	compute_lighting_intensity(t_data *data, long double *hit_point, t_vec *obj_normal)
{
	long double	intensity;
	long double	total_light;
	t_scn_el	**lights;
	int			i;

	intensity = 0;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	total_light = 0;
	i = 0;
	while(lights && lights[i])
	{
		total_light += lights[i]->intensity;
		i++;
	}
	i = 0;
	(void)total_light;
	while (lights && lights[i])
	{
		if (lights[i]->type == AMB_LIGHT)
			intensity += lights[i]->intensity;
		else if (lights[i]->type == LIGHT)
		{
			t_vec *l = create_vec(hit_point, lights[i]->coord);
			long double n_dot_l = dot(obj_normal, l);
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (l->len * obj_normal->len);
		}
		i++;
	}
	if (intensity > 1)
		intensity = 1;
	return (intensity);
}
