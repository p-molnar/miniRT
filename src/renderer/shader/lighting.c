/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:41:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

static t_color	get_ambient_light_color(t_light_fn_arg arg)
{
	t_color	color;

	color.r = fmin(arg.hit_obj.attr->color.r * arg.light.intensity
			* arg.light.color.r / 255., 255);
	color.g = fmin(arg.hit_obj.attr->color.g * arg.light.intensity
			* arg.light.color.g / 255., 255);
	color.b = fmin(arg.hit_obj.attr->color.b * arg.light.intensity
			* arg.light.color.b / 255., 255);
	color.a = 255;
	return (color);
}

static t_color	get_dir_light_col(t_light_fn_arg *arg)
{
	long double	intensity;
	t_color		color;

	arg->light_dir = scale_vec(-1, arg->light.n_vec);
	arg->visibility = intersect((t_ray){arg->hit_obj.inc_p, arg->light_dir},
			arg->objs, (t_range){EPS, INF}, SHADOW).is_hit == false;
	intensity = arg->visibility * arg->light.intensity * fmax(0,
			dot(arg->hit_obj.norm, arg->light_dir));
	color.r = fmin(intensity * arg->hit_obj.attr->color.r * arg->light.color.r
			/ 255.0, 255);
	color.g = fmin(intensity * arg->hit_obj.attr->color.g * arg->light.color.g
			/ 255.0, 255);
	color.b = fmin(intensity * arg->hit_obj.attr->color.b * arg->light.color.b
			/ 255.0, 255);
	color.a = 255;
	return (color);
}

static t_color	get_point_light_color(t_light_fn_arg *arg)
{
	long double	intensity;
	t_color		color;
	long double	len;

	arg->light_dir = create_dir_vec(arg->hit_obj.inc_p, arg->light.pos);
	len = arg->light_dir.len;
	normalize_vec(&arg->light_dir);
	arg->visibility = intersect((t_ray){arg->hit_obj.inc_p, arg->light_dir},
			arg->objs, (t_range){EPS, len},
			SHADOW).is_hit == false;
	intensity = arg->visibility * arg->light.intensity * fmax(0,
			dot(arg->hit_obj.norm, arg->light_dir));
	color.r = fmin(intensity * arg->hit_obj.attr->color.r * arg->light.color.r
			/ 255.0, 255);
	color.g = fmin(intensity * arg->hit_obj.attr->color.g * arg->light.color.g
			/ 255.0, 255);
	color.b = fmin(intensity * arg->hit_obj.attr->color.b * arg->light.color.b
			/ 255.0, 255);
	color.a = 255;
	return (color);
}

static t_color	get_specular_lighting(t_light_fn_arg arg)
{
	long double	specular;
	t_vec3		reflection;
	long double	intensity;
	t_color		color;

	if (arg.hit_obj.attr->spec_coeff < 1)
		return ((t_color){.color = 0x00000000});
	reflection = scale_vec(2 * dot(arg.hit_obj.norm, arg.light_dir),
			arg.hit_obj.norm);
	reflection = subtract_vec(reflection, arg.light_dir);
	normalize_vec(&reflection);
	specular = fmaxl(0, dot(reflection, scale_vec(-1, arg.ray.dir)));
	intensity = arg.visibility * arg.light.intensity * pow(specular,
			arg.hit_obj.attr->spec_coeff);
	color.r = fmin(intensity * arg.hit_obj.attr->color.r * arg.light.color.r
			/ 255.0, 255);
	color.g = fmin(intensity * arg.hit_obj.attr->color.g * arg.light.color.g
			/ 255.0, 255);
	color.b = fmin(intensity * arg.hit_obj.attr->color.b * arg.light.color.b
			/ 255.0, 255);
	color.a = 255;
	return (color);
}

t_color	get_local_color(t_data *data, t_ray ray, t_hit_obj hit_obj)
{
	t_light_fn_arg	arg;
	t_color			hit_color;
	int				i;

	hit_color = (t_color){.r = 0, .g = 0, .b = 0, .a = 255};
	arg = (t_light_fn_arg){.hit_obj = hit_obj, .ray = ray,
		.objs = data->scn_els[ALL_OBJS]};
	i = -1;
	while (data->scn_els[ALL_LIGHTS] && data->scn_els[ALL_LIGHTS][++i])
	{
		arg.light = *data->scn_els[ALL_LIGHTS][i];
		if (arg.light.type == F_AMB_LIGHT)
			hit_color = mix_colors(hit_color, get_ambient_light_color(arg));
		else
		{
			if (arg.light.type == F_DIR_LIGHT)
				hit_color = mix_colors(hit_color, get_dir_light_col(&arg));
			else if (arg.light.type == F_POINT_LIGHT)
				hit_color = mix_colors(hit_color, get_point_light_color(&arg));
			hit_color = mix_colors(hit_color, get_specular_lighting(arg));
		}
	}
	return (hit_color);
}
