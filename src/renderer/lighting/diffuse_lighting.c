/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   diffuse_lighting.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:43:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/06 14:48:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

long double	get_diffuse_lighting(t_data *data, t_scn_el *light)
{
	t_vec3	*light_vec;
	long double	intensity;
	long double	n_dot_l;

	intensity = 0;
	light_vec = NULL;
	if (light->type == F_DIR_LIGHT)
	{
		light_vec = coord_to_vec(light->pos); // revise!
	}
	else if (light->type == F_POINT_LIGHT)
		light_vec = create_dir_vec(*data->p, light->pos);
	n_dot_l = dot(data->v, light_vec);
	if (n_dot_l > 0)
		intensity += light->intensity * n_dot_l / (light_vec->len
				* data->v->len);
	if (light_vec)
		free(light_vec);
	return (intensity);
}