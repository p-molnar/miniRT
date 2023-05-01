/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/01 22:17:01 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

long double	compute_lighting_intensity(t_data *data)
{
	long double	intensity;
	t_scn_el	**lights;
	int			i;
	long double	n_dot_l;

	intensity = 0;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type == AMB_LIGHT)
			intensity += lights[i]->intensity;
		else
		{
			if (lights[i]->type == DIR_LIGHT)
				data->vec[L] = create_vec(NULL, lights[i]->norm_vec);
			else if (lights[i]->type == LIGHT)
				data->vec[L] = create_vec(data->vec[P]->coord, lights[i]->coord);
			n_dot_l = dot(data->vec[N], data->vec[L]);
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (data->vec[L]->len
						* data->vec[N]->len);
		}
		i++;
	}
	return (intensity);
}
