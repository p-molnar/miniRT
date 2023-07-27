/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/27 17:42:15 by pmolnar       ########   odam.nl         */
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
	normalize(&ray.dir);
	return (ray);
}

t_color	trace_ray(t_data *data, t_ray ray, t_range range, int recursion_depth)
{
	t_hit_obj	hit_obj;
	t_color		color[2];
	t_color		ret_color;
	t_ray		reflection;

	hit_obj = intersect(ray, data->scn_els[ALL_OBJS], range);
	if (!hit_obj.el)
		return (BACKGROUND_COLOR);
	reflection.origin = get_incident_point(ray, hit_obj);
	reflection.dir = get_obj_norm(**data->scn_els[CAM], reflection.origin,
			hit_obj);
	color[0] = get_local_color(data, ray, reflection, *hit_obj.el);
	if (recursion_depth > 0 && hit_obj.el->reflection > 0)
		color[1] = get_reflected_color(data, ray, reflection, recursion_depth);
	if (recursion_depth <= 0 || hit_obj.el->reflection <= 0)
		ret_color = color[0];
	else
		ret_color = mix_colors(color[0], color[1], hit_obj.el->reflection);
	return (ret_color);
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
	c.pixel_y = 0;
	while (c.pixel_y < height)
	{
		c.pixel_x = 0;
		while (c.pixel_x < width)
		{
			c.x = (2 * ((c.pixel_x + 0.5) / (float)width) - 1) * aspect_ratio
				* fov_scale;
			c.y = (1 - 2 * (c.pixel_y + 0.5) / (float)height) * fov_scale;
			ray = transform_ray(data, c, ray);
			color = trace_ray(data, ray, (t_range){1, INF}, 0);
			mlx_put_pixel(data->img, c.pixel_x, c.pixel_y, color);
			c.pixel_x++;
		}
		c.pixel_y++;
	}
}
