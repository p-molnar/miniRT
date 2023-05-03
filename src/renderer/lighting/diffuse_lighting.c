/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   diffuse_lighting.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:43:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 14:04:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

long double	get_diffuse_lighting(t_data *data, t_scn_el *light)
{
	long double	intensity;
	long double	n_dot_l;

	intensity = 0;
	if (light->type == AMB_LIGHT)
		intensity += light->intensity;
	else
	{
		if (light->type == DIR_LIGHT)
		{
			data->vec[L] = create_vec(NULL, light->coord); // revise!
			// data->vec[L] = scale(-1, data->vec[L]);
		}
		else if (light->type == LIGHT)
			data->vec[L] = create_vec(data->vec[P]->coord, light->coord);
		n_dot_l = dot(data->vec[N], data->vec[L]);
		if (n_dot_l > 0)
			intensity += light->intensity * n_dot_l / (data->vec[L]->len
					* data->vec[N]->len);
	}
	return (intensity);
}
