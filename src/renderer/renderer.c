/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/29 11:41:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	*get_incident_point_norm(t_coord3 *inc_p, t_closest *obj)
{
	t_vec3	*norm;

	norm = NULL;
	if (obj->el->type == CYLINDER)
	{
		if ((inc_p[Z] > obj->el->cap[0].coord[Z] && inc_p[Z] < obj->el->cap[1].coord[Z]))
			norm = create_vec(create_coord(0, 0, inc_p[Z]), inc_p);	
		else
		{
			if (inc_p[Z] < obj->el->coord[Z])
				norm = create_vec(inc_p, create_coord(inc_p[X], inc_p[Y], inc_p[Z] - 1));
			else
				norm = create_vec(inc_p, create_coord(inc_p[X], inc_p[Y], inc_p[Z] + 1));
		}
	}
	else if (obj->el->type == SPHERE)
		norm = create_vec(obj->el->coord, inc_p);
	else if (obj->el->type == PLANE)
	{	
		norm = create_vec(NULL, obj->el->n_vec->dir);
	}
	norm = get_normal_vec(norm);
	return (norm); 
}

t_color	trace_ray(t_data *data, long double *origin, t_vec3 *dir,
		const long double *range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_scn_el			**el_arr;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {0 + EPS, INF};

	el_arr = get_scn_els(data->scn_el, G_OBJS);
	closest_obj = get_closest_el(el_arr, origin, dir, range);
	if (!closest_obj || !closest_obj->el)
		return (BACKGROUND_COLOR);
	data->p[INCIDENT] = get_incident_point(origin, dir, closest_obj->dist);
	data->v[NORM] = get_incident_point_norm(data->p[INCIDENT], closest_obj);
	color[0] = get_incident_point_color(data, data->p[INCIDENT], closest_obj->el);
	ref_factor = closest_obj->el->reflection;
	free(closest_obj);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (color[0]);
	color[1] = get_reflected_color(data, dir, ref_range, recursion_depth);
	return (mix_colors(color[0], color[1], ref_factor));
}

t_vec3	*rotate_ray(t_data *d, t_vec3 *ray, long double agl, t_vec3 *ax)
{
	t_mx *ray_mx;
	t_mx *axis_mx;
	t_mx *rotated_mx;

	(void) d;
	ray_mx = coord_to_mx(ray->dir);
	ray_mx = expand_mx(ray_mx, 4, 4, 1);
	axis_mx = coord_to_mx(ax->dir);
	axis_mx = expand_mx(axis_mx, 4, 4, 1);
	rotated_mx = rotate_mx(ray_mx, axis_mx, agl);
	if (fabsl(agl) > M_PI_2 && ax->dir[X] == 1)
	{
		t_vec3 *cam_tg = get_normal_vec(create_vec(d->cam->coord, d->cam->tg_coord));
		t_mx *ax_mx = expand_mx(coord_to_mx(cam_tg->dir), 4, 4, 1);	
		rotated_mx = rotate_mx(rotated_mx, ax_mx, M_PI);
	}
	return (create_vec(NULL, create_coord(rotated_mx->m[0], rotated_mx->m[1], rotated_mx->m[2])));
}

void	render_img(t_data *data)
{
	int					canvas[2];
	int					screen[2];
	int					counter;
	t_color				color;
	long double			*pplane_coord;
	const long double	range[RANGE_SIZE] = {1, INF};
	
	canvas[X] = -CANVAS_W / 2;
	counter = 0;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			init_vec(data->v, VEC_SIZE);
			pplane_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport, data->cam);
			data->v[RAY] = create_vec(data->cam->coord, pplane_coord);
			data->v[RAY] = rotate_ray(data, data->v[RAY], data->rot_angle, data->rot_axis);
			// printf("%d\n", counter);
			// if (data->vec[D]->coord[0] == 0 && data->vec[D]->coord[1] == 0 && data->vec[D]->coord[2] == 1)
			// 	printf("this\n");	
			// printf("%Lf, %Lf, %Lf\n", data->vec[D]->coord[0], data->vec[D]->coord[1], data->vec[D]->coord[2]);
			color = trace_ray(data, data->cam->coord, data->v[RAY], range, 2);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			free(pplane_coord);
			free_vec(data->v, VEC_SIZE);
			counter++;
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
}
