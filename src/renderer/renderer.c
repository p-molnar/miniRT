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


t_color	trace_ray(t_data *data, t_ray *ray, const long double *range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_color				color[2];
	t_color				ret_color;
	t_ray				sec_ray;

	closest_obj = get_closest_el(data->scn_els[ALL_OBJS], ray, range);
	if (closest_obj && !closest_obj->el)
	{
		if (closest_obj->inc_p)
			free(closest_obj->inc_p);
		free(closest_obj);
		closest_obj = NULL;
		return (BACKGROUND_COLOR);
	}
	sec_ray.origin = get_incident_point(ray, closest_obj);
	sec_ray.dir = get_incident_point_norm(*data->scn_els[CAM], sec_ray.origin, closest_obj);
	color[0] = get_local_color(data, ray, sec_ray, closest_obj->el);
	if (recursion_depth > 0 || closest_obj->el->reflection > 0)
		color[1] = get_reflected_color(data, ray, sec_ray, recursion_depth);
	if (recursion_depth <= 0 || closest_obj->el->reflection <= 0)
		ret_color = color[0];
	else
		ret_color = mix_colors(color[0], color[1], closest_obj->el->reflection);
	if (closest_obj->inc_p)
		free(closest_obj->inc_p);
	free(closest_obj);
	free(sec_ray.origin);
	free(sec_ray.dir);
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
	const long double	range[RANGE_SIZE] = {1, INF};
	t_color	color;
	t_ray 	ray;
	t_mx*	dir_mx;
	t_mx*	tmp;
	t_coord3	*dir;

	color = 0;
	aspect_ratio = CANVAS_W / CANVAS_H; 
	ray.origin = &data->scn_els[CAM][0]->pos;
	fov_scale = tan(deg_to_rad((*data->scn_els[CAM])->fov / 2));
	y = 0;
	while (y < CANVAS_H)
	{
		x = 0;
		while (x < CANVAS_W)
		{
		    pixel_x = (2 * ((x + 0.5) / CANVAS_W) - 1) * fov_scale * aspect_ratio;
      		pixel_y = (1 - 2 * (y + 0.5) / CANVAS_H) * fov_scale;
			dir = create_coord(pixel_x, pixel_y, 1);
			dir_mx = coord_to_mx(dir, 3, 1);
			free(dir);
			expand_mx(dir_mx, 4, 1, 0);
			tmp = multiply_mx(data->ctw_mx, dir_mx);
			free_mx(dir_mx);
			ray.dir = create_vec(tmp->m[X], tmp->m[Y], tmp->m[Z]);
			free_mx(tmp);
			normalize(ray.dir);
			color = trace_ray(data, &ray, range, 0);
			mlx_put_pixel(data->img, x, y, color);
			free(ray.dir);
			x++;
		}
		y++;
	}
	// draw_axes(data);
}
