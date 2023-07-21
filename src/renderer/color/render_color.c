/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:57:27 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 13:31:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_color	get_local_color(t_data *data, t_ray ray, t_ray reflection_ray, t_scn_el *closest_el)
{
	t_color		tmp_color;
	t_color		color;
	long double	intensity;
	int			i;

	intensity = get_lighting_intensity(data, ray, reflection_ray, closest_el);
	color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		tmp_color = get_color(closest_el->color, i);
		color = update_color_channel(color, tmp_color * intensity, i);
		i++;
	}
	return (color);
}

t_color	mix_colors(t_color local_color, t_color reflected_color, long double ref_factor)
{
	t_color	color;
	t_color	c1;
	t_color	c2;
	int		i;

	color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		c1 = get_color(local_color, i) * (1 - ref_factor);
		c2 = get_color(reflected_color, i) * ref_factor;
		color = update_color_channel(color, c1 + c2, i);
		i++;
	}
	return (color);
}

t_color	get_reflected_color(t_data *data, t_ray ray, t_ray sec_ray, int depth)
{
	t_color	reflected_color;
	t_ray	reflected_ray;

	reflected_ray.origin = sec_ray.origin;
	reflected_ray.dir = get_reflection_ray(scale(-1, ray.dir), sec_ray.dir);
	reflected_color = trace_ray(data, reflected_ray, (t_range){EPS, INF}, depth - 1);
	return (reflected_color);
}