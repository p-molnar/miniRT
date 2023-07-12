/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:57:27 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/12 12:51:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_color	get_local_color(t_data *data, t_ray *ray, t_ray reflection_ray, t_scn_el *closest_el)
{
	t_color		tmp_color;
	t_color		color;
	t_color		new_color;
	long double	intensity;
	int			i;

	intensity = get_lighting_intensity(data, ray, reflection_ray, closest_el);
	color.color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		tmp_color = get_color(closest_el->color, i);
		new_color.color = tmp_color.color * intensity;
		color = update_color_channel(color, new_color, i);
		i++;
	}
	return (color);
}

t_color	mix_colors(t_color local_color, t_color reflected_color, long double ref_factor)
{
	t_color	color;
	t_color	mixed_color;
	int		c1;
	int		c2;
	int		i;

	color.color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		c1 = get_color(local_color, i).color * (1 - ref_factor);
		c2 = get_color(reflected_color, i).color * ref_factor;
		mixed_color.color = c1 + c2;
		color = update_color_channel(color, mixed_color, i);
		i++;
	}
	return (color);
}

t_color	get_reflected_color(t_data *data, t_ray *ray, t_ray sec_ray, int depth)
{
	t_color	reflected_color;
	t_vec3	*obj_to_cam;
	t_ray	reflected_ray;
	const long double	ref_range[RANGE_SIZE] = {EPS, INF};

	reflected_ray.origin = sec_ray.origin;
	obj_to_cam = scale(-1, ray->dir);
	reflected_ray.dir = get_reflection_ray(obj_to_cam, sec_ray.dir);
	reflected_color = trace_ray(data, &reflected_ray, ref_range, depth - 1);
	free(obj_to_cam);
	free(reflected_ray.dir);
	return (reflected_color);
}