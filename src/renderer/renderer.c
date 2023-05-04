/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/04 17:13:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_vec	*get_ray_reflection(t_vec *ray, t_vec *norm)
{
	long double	ray_dot_norm;
	t_vec		*scaled_vec;
	t_vec		*scaled_minus_ray;

	if (!ray || !norm)
		return (NULL);
	ray_dot_norm = dot(ray, norm);
	scaled_vec = scale(2 * ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}

t_vec	*get_incident_point(long double	*start_coord, t_vec *direction, long double distance)
{
	t_vec	*O;
	t_vec	*scaled_dir;
	t_vec	*incident_point;


	O = create_vec(start_coord, start_coord);
	scaled_dir = scale(distance, direction);
	incident_point = add(O, scaled_dir);
	return (incident_point);
}

t_color	trace_ray(t_data *data, long double *start_coord, t_vec *dir,
	const long double *range, int recursion_depth)
{
	t_closest			*closest;
	t_scn_el			**el_arr;
	t_color				local_color;
	t_color				reflected_color;
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {0.001, INF};

	el_arr = get_scn_els(data->scn_el, SPHERE);
	closest = get_closest_el(el_arr, start_coord, dir, range);
	if (closest->el == NULL)
		return (BACKGROUND_COLOR);
	data->vec[P] = get_incident_point(start_coord, dir, closest->dist);
	data->vec[N] = create_vec(closest->el->coord, data->vec[P]->coord);
	normalize_vec(data->vec[N]);
	local_color = get_incident_point_color(data, closest->el);
	ref_factor = closest->el->reflection;
	free(closest);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (local_color);
	data->vec[Dneg] = scale(-1, dir);
	data->vec[Rv] = get_ray_reflection(data->vec[Dneg], data->vec[N]);
	reflected_color = trace_ray(data, data->vec[P]->coord, data->vec[Rv], ref_range, recursion_depth - 1);
	free_vec(data->vec, VEC_SIZE);
	t_color color;
	color = 0xFFFFFFFF;
	int i = 1;
	while (i < COLOR_SIZE)
	{
		t_color c1 = get_color(local_color, i) * (1 - ref_factor);
		t_color c2 = get_color(reflected_color, i) * ref_factor;
		color = update_color_channel(color, c1 + c2, i);
		i++;
	}
	return (color);
}

void	render_img(t_data *data)
{
	int			canvas[2];
	int			screen[2];
	t_color		color;
	long double	*vp_coord;
	const long double	range[RANGE_SIZE] = {1, INF};

	canvas[X] = -CANVAS_W / 2;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			vp_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport);
			data->vec[D] = create_vec(data->cam->coord, vp_coord);
			color = trace_ray(data, data->cam->coord, data->vec[D], range, 3);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			free(vp_coord);
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
}
