/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:41:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>

t_ray	transform_ray(t_data *d, t_coord_sys c, t_ray ray)
{
	t_mx	dir_mx;

	ray.origin = d->scn_els[CAM][0]->pos;
	dir_mx = coord_to_mx((t_coord3){{c.x, c.y, 1}}, 4, 1, 0);
	dir_mx = multiply_mx(d->ctw_mx, dir_mx);
	ray.dir = create_vec(dir_mx.m[X], dir_mx.m[Y], dir_mx.m[Z]);
	normalize_vec(&ray.dir);
	return (ray);
}

t_color	trace_ray(t_data *data, t_ray ray, t_range range, int recursion_depth)
{
	t_hit_obj	hit_obj;
	t_color		local_color;
	t_color		reflected_color;

	hit_obj = intersect(ray, data->scn_els[ALL_OBJS], range, CLOSEST_EL);
	if (!hit_obj.is_hit)
		return ((t_color){.r = 0, .g = 0, .b = 0, .a = 255});
	get_incident_point(ray, &hit_obj);
	get_surface_norm(**data->scn_els[CAM], &hit_obj);
	local_color = get_local_color(data, ray, hit_obj);
	reflected_color = get_reflected_color(data, ray, hit_obj, recursion_depth);
	if (recursion_depth != 0 && hit_obj.attr->refl_coeff > 0)
	{
		local_color = intensify_color(1 - hit_obj.attr->refl_coeff,
				local_color);
		reflected_color = intensify_color(hit_obj.attr->refl_coeff,
				reflected_color);
	}
	return (mix_colors(local_color, reflected_color));
}

void	render_scene(t_data *data, int width, int height)
{
	t_coord_sys	c;
	long double	aspect_ratio;
	long double	fov_scale;
	t_color		color;
	t_ray		ray;

	aspect_ratio = width / (float)height;
	fov_scale = tan(deg_to_rad((*data->scn_els[CAM])->fov / 2));
	c.pixel_y = -1;
	while (++c.pixel_y < height)
	{
		c.pixel_x = -1;
		while (++c.pixel_x < width)
		{
			c.x = (2 * ((c.pixel_x + 0.5) / (float)width) - 1) * aspect_ratio
				* fov_scale;
			c.y = (1 - 2 * (c.pixel_y + 0.5) / (float)height) * fov_scale;
			ray = transform_ray(data, c, ray);
			color = trace_ray(data, ray, (t_range){1, INF}, 1);
			mlx_put_pixel(data->img, c.pixel_x, c.pixel_y, color.color);
		}
	}
}
