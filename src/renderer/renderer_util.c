/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 10:37:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

long double	*get_cylinder_intersection(t_data *data, t_scn_el *obj)
{
	long double	*t;
	long double	a;
	long double	b;
	long double	c;
	long double *r;

	r = ft_calloc(2, sizeof(long double));
	a = pow(data->vec[D]->coord[X], 2) + pow(data->vec[D]->coord[Y], 2);
	b = 2 * data->cam->coord[X] * data->vec[D]->coord[X] + 2 * data->cam->coord[Y] * data->vec[D]->coord[Y];
	c = pow(data->cam->coord[X], 2) + pow(data->cam->coord[Y], 2) - obj->diameter / 2;
	t = quad_eq_solver(a, b, c, NULL);
	if (!t)
		return (r);
	long double z1 = data->cam->coord[Z] + t[0] * data->vec[D]->coord[Z];
	long double z2 = data->cam->coord[Z] + t[1] * data->vec[D]->coord[Z];
	if (3 < z1 && z1 < 13)
		r[0] = t[0];
	if (3 < z2 && z2 < 13)
		r[1] = t[1];
	return (r);
}

t_closest	*get_closest_el(t_data *data, t_scn_el **el_arr, long double start_coord[3], t_vec3 *dir, const long double *range)
{
	t_closest	*closest;
	long double	*t;
	int			i;
	(void) start_coord, (void) dir;

	closest = ft_calloc(1, sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	i = 0;
	while (el_arr && el_arr[i])
	{
		if (el_arr[i]->type == SPHERE)
			t = get_intersection_points(start_coord, dir, el_arr[i]);
		else if (el_arr[i]->type == CYLINDER)
			t = get_cylinder_intersection(data, el_arr[i]);
		else if (el_arr[i]->type == PLANE)
			t = get_plane_intersection(data, el_arr[i]);
		if (is_in_range_f(t[0], range[MIN], range[MAX]) && t[0] < closest->dist)
		{
			closest->dist = t[0];
			closest->el = el_arr[i];
		}
		if (is_in_range_f(t[1], range[MIN], range[MAX]) && t[1] < closest->dist)
		{
			closest->dist = t[1];
			closest->el = el_arr[i];
		}
		i++;
	}
	free(t);
	return (closest);
}

long double	*get_plane_intersection(t_data *data, t_scn_el *obj)
{
	long double	*t;
	t_vec3		*Q;
	t_vec3		*E;
	t_vec3		*Q_less_E;
	long double	denom;

	t = malloc(2 * sizeof(long double));
	Q = create_vec(NULL, obj->coord);
	E = create_vec(NULL, data->cam->coord);
	Q_less_E = subtract(Q, E);
	denom = dot(obj->n_vec, data->vec[D]);
	if (fabs(denom) > 0.0001)
	{
		t[0] = dot(obj->n_vec, Q_less_E) / denom;
		t[1] = t[0];
	}
	else
	{
		t[0] = 0;
		t[1] = 0;
	}
	return (t);
}

long double	*get_intersection_points(long double start[3], t_vec3 *dir, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;
	t_vec3		*CO;

	CO = create_vec(obj->coord, start);
	quad_param[0] = dot(dir, dir);
	quad_param[1] = 2.0 * dot(CO, dir);
	quad_param[2] = dot(CO, CO) - pow(obj->radius, 2);
	t = quad_eq_solver(quad_param[0], quad_param[1], quad_param[2], &d);
	free(CO);
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

long double	*convert_to_viewport(int x, int y, long double *viewport, t_scn_el *cam)
{
	long double	*pplane;

	pplane = malloc(COORD_SIZE * sizeof(long double));
	if (!pplane)
		error(ft_strdup("Malloc error\n"), EXIT, 1);
	pplane[X] = x * viewport[X] / CANVAS_W + cam->coord[X];
	pplane[Y] = y * viewport[Y] / CANVAS_H + cam->coord[Y];
	pplane[Z] = viewport[Z] + cam->coord[Z];
	return (pplane);
}

t_vec3	*get_ray_reflection(t_vec3 *ray, t_vec3 *norm)
{
	long double	ray_dot_norm;
	t_vec3		*scaled_vec;
	t_vec3		*scaled_minus_ray;

	if (!ray || !norm)
		return (NULL);
	ray_dot_norm = 2 * dot(ray, norm);
	scaled_vec = scale(ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}