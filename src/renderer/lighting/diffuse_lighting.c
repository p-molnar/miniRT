/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   diffuse_lighting.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:43:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/09 09:06:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

long double	get_diffuse_lighting(t_data *data, t_scn_el *light)
{
	long double	intensity;
	long double	n_dot_l;

	intensity = 0;
	if (light->type == F_DIR_LIGHT)
	{
		data->v[LIGHT] = coord_to_vec(light->pos); // revise!
	}
	else if (light->type == F_POINT_LIGHT)
		data->v[LIGHT] = create_dir_vec(*data->p[INCIDENT], light->pos);
	n_dot_l = dot(data->v[NORM], data->v[LIGHT]);
	if (n_dot_l > 0)
		intensity += light->intensity * n_dot_l / (data->v[LIGHT]->len
				* data->v[NORM]->len);
	return (intensity);
}