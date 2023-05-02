/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/02 16:20:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

long double	*convert_to_viewport(int x, int y, long double *viewport)
{
	long double	*coord;

	coord = malloc(COORD_SIZE * sizeof(long double));
	if (!coord)
		error(ft_strdup("Malloc error\n"), EXIT, 1);
	coord[X] = x * viewport[X] / CANVAS_W;
	coord[Y] = y * viewport[Y] / CANVAS_H;
	coord[Z] = 1;
	return (coord);
}

int	get_computed_color(t_data *data, t_color obj_color)
{
	t_color		tmp_color;
	long double	intensity;
	int			i;

	intensity = compute_lighting_intensity(data);
	i = 1;
	while (i < COLOR_SIZE)
	{
		tmp_color = get_color(obj_color, i);
		obj_color = update_color_channel(obj_color, tmp_color * intensity, i);
		i++;
	}
	return (obj_color);
}

long double	*get_intersection_points(t_data *data, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;

	quad_param[0] = dot(data->vec[D], data->vec[D]);
	quad_param[1] = 2.0 * dot(data->vec[CO], data->vec[D]);
	quad_param[2] = dot(data->vec[CO], data->vec[CO]) - pow(obj->radius, 2);
	t = quad_eq_solver(quad_param[0], quad_param[1], quad_param[2], &d);
	if (d < 0)
	{
		t = malloc(2 * sizeof(long double));
		if (!t)
			return (NULL);
		t[0] = INF;
		t[1] = INF;
	}
	return (t);
}

t_scn_el	*get_closest_el(t_data *data, long double *closest_t)
{
	long double	*t;
	t_scn_el	*closest_el;
	t_scn_el	**spheres;
	int			i;

	closest_el = NULL;
	spheres = get_scn_els(data->scn_el, SPHERE);
	i = 0;
	while (spheres && spheres[i])
	{
		data->vec[CO] = create_vec(spheres[i]->coord, data->cam->coord);
		t = get_intersection_points(data, spheres[i]);
		if (is_in_range_f(t[0], 1, INF) && t[0] < *closest_t)
		{
			*closest_t = t[0];
			closest_el = spheres[i];
			// printf("intersection 0\n");
		}
		if (is_in_range_f(t[1], 1, INF) && t[1] < *closest_t)
		{
			*closest_t = t[1];
			closest_el = spheres[i];
			// printf("intersection 1\n");
		}
		i++;
	}
	free(t);
	return (closest_el);
}

t_color	trace_ray(t_data *data, long double *cam_coord,
		long double *pplane_coord)
{
	t_scn_el	*closest_el;
	long double	dist_to_el;

	dist_to_el = INF;
	data->vec[D] = create_vec(cam_coord, pplane_coord);
	closest_el = get_closest_el(data, &dist_to_el);
	if (closest_el == NULL)
		return (data->bg);
	else
	{
		data->vec[O] = create_vec(cam_coord, cam_coord);
		scale(dist_to_el, data->vec[D]);
		data->vec[P] = add(data->vec[O], data->vec[D]);
		data->vec[N] = create_vec(closest_el->coord, data->vec[P]->coord); //modified
		normalize_vec(data->vec[N]); // might not be needed
		return (get_computed_color(data, closest_el->color));
	}
}

void	draw_axes(t_data *data)
{
	int		x;
	int		y;
	t_color	c;

	c = 0xFF0000FF;
	x = 0;
	while (x < CANVAS_W)
		mlx_put_pixel(data->img, x++, CANVAS_H / 2, c);
	y = 0;
	while (y < CANVAS_H)
		mlx_put_pixel(data->img, CANVAS_W / 2, y++, c);
}

void	render_img(t_data *data)
{
	int			canvas[2];
	int			screen[2];
	t_color		color;
	long double	*vp_coord;
	t_scn_el	**cam;

	cam = get_scn_els(data->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found"), EXIT, 1);
	canvas[X] = -CANVAS_W / 2;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			init_vec(data->vec, PARAM_SIZE);
			vp_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport);
			color = trace_ray(data, cam[0]->coord, vp_coord);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			free(vp_coord);
			free_vec(data->vec, PARAM_SIZE);
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
	free(cam);
}
