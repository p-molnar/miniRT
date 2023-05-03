/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 15:41:42 by pmolnar       ########   odam.nl         */
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

int	compute_color(t_data *data, t_scn_el *closest_el)
{
	t_color		tmp_color;
	t_color		color;
	long double	intensity;
	int			i;

	intensity = compute_lighting_intensity(data, closest_el->specular);
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

long double	*get_intersection_points(t_data *data, long double start[3], t_vec *dir, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;

	data->vec[CO] = create_vec(obj->coord, start);
	quad_param[0] = dot(dir, dir);
	quad_param[1] = 2.0 * dot(data->vec[CO], dir);
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

t_closest	*get_closest_el(t_data *data, long double start[3], t_vec *dir)
{
	t_closest	*closest;
	long double	*t;
	t_scn_el	**spheres;
	int			i;

	closest = ft_calloc(1, sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->dist = INF;
	spheres = get_scn_els(data->scn_el, SPHERE);
	i = 0;
	while (spheres && spheres[i])
	{
		t = get_intersection_points(data, start, dir, spheres[i]);
		if (is_in_range_f(t[0], 1, INF) && t[0] < closest->dist)
		{
			closest->dist = t[0];
			closest->el = spheres[i];
		}
		if (is_in_range_f(t[1], 1, INF) && t[1] < closest->dist)
		{
			closest->dist = t[1];
			closest->el = spheres[i];
		}
		i++;
	}
	free(t);
	return (closest);
}

t_color	trace_ray(t_data *data, long double *cam_coord,
		long double *pplane_coord)
{
	t_closest	*closest;
	t_color		color;

	color = BACKGROUND_COLOR;
	data->vec[D] = create_vec(cam_coord, pplane_coord);
	closest = get_closest_el(data, cam_coord, data->vec[D]);
	if (closest->el != NULL)
	{
		data->vec[O] = create_vec(cam_coord, cam_coord);
		data->vec[Ds] = scale(closest->dist, data->vec[D]);
		data->vec[P] = add(data->vec[O], data->vec[Ds]);
		data->vec[N] = create_vec(closest->el->coord, data->vec[P]->coord);
		normalize_vec(data->vec[N]); // might not be needed
		color = compute_color(data, closest->el);
		// if (color != 255)
		// 	printf("color: %d\n", color);
	}
	return (color);
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
