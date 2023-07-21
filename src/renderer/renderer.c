/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/06 15:10:50by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>


t_color	trace_ray(t_data *data, t_ray ray, t_range range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_color				color[2];
	t_color				ret_color;
	t_ray				sec_ray;

	closest_obj = get_closest_el(data->scn_els[ALL_OBJS], ray, range);
	if (closest_obj && !closest_obj->el)
	{
		free(closest_obj);
		return (BACKGROUND_COLOR);
	}
	sec_ray.origin = get_incident_point(ray, closest_obj);
	sec_ray.dir = get_incident_point_norm(**data->scn_els[CAM], sec_ray.origin, closest_obj);
	color[0] = get_local_color(data, ray, sec_ray, closest_obj->el);
	if (recursion_depth > 0 && closest_obj->el->reflection > 0)
		color[1] = get_reflected_color(data, ray, sec_ray, recursion_depth);
	if (recursion_depth <= 0 || closest_obj->el->reflection <= 0)
		ret_color = color[0];
	else
		ret_color = mix_colors(color[0], color[1], closest_obj->el->reflection);
	free(closest_obj);
	return (ret_color);
}

void	render_scene(t_data *data)
{
	int	y;
	int	x;
	long double	pixel_x;
	long double	pixel_y;
	long double	aspect_ratio;
	long double	fov_scale;
	t_color	color;
	t_ray 	ray;
	t_mx	dir_mx;

	color = 0;
	aspect_ratio = CANVAS_W / CANVAS_H; 
	ray.origin = data->scn_els[CAM][0]->pos;
	fov_scale = tan(deg_to_rad((*data->scn_els[CAM])->fov / 2));
	y = 0;
	while (y < CANVAS_H)
	{
		x = 0;
		while (x < CANVAS_W)
		{
		    pixel_x = (2 * ((x + 0.5) / CANVAS_W) - 1) * fov_scale * aspect_ratio;
      		pixel_y = (1 - 2 * (y + 0.5) / CANVAS_H) * fov_scale;
			dir_mx = coord_to_mx((t_coord3) {{pixel_x, pixel_y, 1}}, 4, 1, 0);
			dir_mx = multiply_mx(data->ctw_mx, dir_mx);
			ray.dir = create_vec(dir_mx.m[X], dir_mx.m[Y], dir_mx.m[Z]);
			normalize(&ray.dir);
			color = trace_ray(data, ray, (t_range){1, INF}, 0);
			mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
	// draw_axes(data);
}
