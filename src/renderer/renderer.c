/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/17 16:42:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	*get_incident_point_norm(t_data *data, t_vec3 *incident_p, t_closest *obj)
{
	t_vec3	*norm;
	// t_vec3	*offset;
	(void) data;

	norm = NULL;
	if (obj->el->type == CYLINDER)
	{
		long double z = incident_p->coord[Z];
		long double a[3] = {0, 0, z};
		norm = create_vec(a, incident_p->coord);
	}
	else if (obj->el->type == SPHERE)
		norm = create_vec(obj->el->coord, incident_p->coord);
	else if (obj->el->type == PLANE || obj->el->type == CYLINDER_CAP)
	{
		// t_coord3 c = create_coord();
		// t_mx4 trans_mx = create_translation_mx(c);
		// norm = translate(obj->el->n_vec,)
	}
	normalize_vec(norm);
	return (norm); 
}

t_color	trace_ray(t_data *data, long double *start_coord, t_vec3 *dir,
		const long double *range, int recursion_depth)
{
	t_closest			*closest;
	t_scn_el			**el_arr;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {0 + EPS, INF};

	// el_arr = get_scn_els(data->scn_el, SPHERE);
	el_arr = get_scn_els(data->scn_el, PLANE | SPHERE | CYLINDER);
	closest = get_closest_el(data, el_arr, start_coord, dir, range);
	if (!closest || !closest->el)
		return (BACKGROUND_COLOR);
	data->vec[P] = get_incident_point(start_coord, dir, closest->dist);
	data->vec[N] = get_incident_point_norm(data, data->vec[P], closest);
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

	r_ray = vec_times_mx(ray, rotation_mx, 3 * 3);
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
	// draw_axes(data);
}
