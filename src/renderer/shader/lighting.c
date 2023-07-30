/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/30 15:37:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_color	get_ambient_light_color(t_scn_el light, t_hit_obj hit_obj)
{
	t_color	color;

	color.r = fmin(hit_obj.attr->color.r * light.intensity * light.color.r
			/ 255., 255);
	color.g = fmin(hit_obj.attr->color.g * light.intensity * light.color.g
			/ 255., 255);
	color.b = fmin(hit_obj.attr->color.b * light.intensity * light.color.b
			/ 255., 255);
	color.a = 255;
	return (color);
}

t_color	get_dir_light_color(t_data data, t_scn_el light, t_hit_obj hit_obj)
{
	t_vec3		light_dir;
	long double	intensity;
	bool		visibility;
	t_color		color;

	light_dir = scale(-1, light.n_vec);
	visibility = intersect(
			(t_ray){hit_obj.inc_p, light_dir}, data.scn_els[ALL_OBJS],
			(t_range){EPS, INF}, SHADOW).is_hit == false;
	intensity = visibility * light.intensity * fmax(0, dot(hit_obj.norm,
				light_dir));
	color.r = fmin(intensity * hit_obj.attr->color.r * light.color.r / 255.0,
			255);
	color.g = fmin(intensity * hit_obj.attr->color.g * light.color.g / 255.0,
			255);
	color.b = fmin(intensity * hit_obj.attr->color.b * light.color.b / 255.0,
			255);
	color.a = 255;
	return (color);
}

t_color	get_point_light_color(t_data data, t_scn_el light, t_hit_obj hit_obj)
{
	t_vec3		light_dir;
	bool		visibility;
	long double	intensity;
	t_color		color;

	light_dir = create_dir_vec(hit_obj.inc_p, light.pos);
	visibility = intersect(
			(t_ray){hit_obj.inc_p, light_dir}, data.scn_els[ALL_OBJS],
			(t_range){EPS, INF}, SHADOW).is_hit == false;
	normalize(&light_dir);
	intensity = visibility * light.intensity * fmax(0, dot(hit_obj.norm,
				light_dir));
	color.r = fmin(intensity * hit_obj.attr->color.r * light.color.r / 255.0,
			255);
	color.g = fmin(intensity * hit_obj.attr->color.g * light.color.g / 255.0,
			255);
	color.b = fmin(intensity * hit_obj.attr->color.b * light.color.b / 255.0,
			255);
	color.a = 255;
	return (color);
}

t_color	get_local_color(t_data *data, t_hit_obj hit_obj)
{
	t_scn_el	*light;
	t_color		hit_color;
	int			i;

	hit_color = (t_color){.r = 0, .g = 0, .b = 0, .a = 255};
	i = 0;
	while (data->scn_els[ALL_LIGHTS] && data->scn_els[ALL_LIGHTS][i])
	{
		light = data->scn_els[ALL_LIGHTS][i];
		if (light->type == F_AMB_LIGHT)
			hit_color = sum_colors(hit_color, get_ambient_light_color(*light,
						hit_obj));
		else if (light->type == F_DIR_LIGHT)
			hit_color = sum_colors(hit_color, get_dir_light_color(*data, *light,
						hit_obj));
		else if (light->type == F_POINT_LIGHT)
			hit_color = sum_colors(hit_color, get_point_light_color(*data,
						*light, hit_obj));
		i++;
	}
	return (hit_color);
}
