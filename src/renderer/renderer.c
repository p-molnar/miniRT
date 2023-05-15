/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/11 13:25:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_color	trace_ray(t_data *data, long double *start_coord, t_vec3 *dir,
		const long double *range, int recursion_depth)
{
	t_closest			*closest;
	t_scn_el			**el_arr;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {0.001, INF};

	// el_arr = get_scn_els(data->scn_el, SPHERE);
	el_arr = get_scn_els(data->scn_el, PLANE | SPHERE | CYLINDER);
	closest = get_closest_el(data, el_arr, start_coord, dir, range);
	if (!closest || !closest->el)
		return (BACKGROUND_COLOR);
	data->vec[P] = get_incident_point(start_coord, dir, closest->dist);
	if (closest->el->type == CYLINDER)
	{
		long double z = data->vec[P]->coord[Z];
		long double a[3] = {0, 0, z};
		data->vec[N] = create_vec(a, data->vec[P]->coord);
		// data->vec[N] = create_vec(NULL, closest->el->n_vec->n_coord);
	}
	else if (closest->el->type == SPHERE)
		data->vec[N] = create_vec(closest->el->coord, data->vec[P]->coord);
	else if (closest->el->type == PLANE)
		data->vec[N] = create_vec(NULL, closest->el->n_vec->n_coord);
	normalize_vec(data->vec[N]);
	color[0] = get_incident_point_color(data, closest->el);
	ref_factor = closest->el->reflection;
	free(closest);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (color[0]);
	color[1] = get_reflected_color(data, dir, ref_range, recursion_depth);
	return (mix_colors(color[0], color[1], ref_factor));
}

t_vec3	*rotate_ray(t_vec3 *ray, long double *rotation_mx)
{
	t_vec3	*r_ray;

	r_ray = vec_times_mx(ray, rotation_mx);
	free(ray);
	return (r_ray);
}

void	render_img(t_data *data)
{
	int					canvas[2];
	int					screen[2];
	t_color				color;
	long double			*pplane_coord;
	const long double	range[RANGE_SIZE] = {1, INF};
	
	canvas[X] = -CANVAS_W / 2;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			// init_vec(data->vec, VEC_SIZE);
			pplane_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport, data->cam);
			data->vec[D] = create_vec(data->cam->coord, pplane_coord);
			data->vec[D] = rotate_ray(data->vec[D], data->rotation_mx);
			// if (data->vec[D]->coord[0] == 0 && data->vec[D]->coord[1] == 0 && data->vec[D]->coord[2] == 1)
			// 	printf("this\n");	
			// printf("%Lf, %Lf, %Lf\n", data->vec[D]->coord[0], data->vec[D]->coord[1], data->vec[D]->coord[2]);
			color = trace_ray(data, data->cam->coord, data->vec[D], range, 0);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			// free_vec(data->vec, VEC_SIZE);
			free(pplane_coord);
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
}
