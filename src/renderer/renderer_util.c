/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/08 13:56:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
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

t_closest	*get_closest_el(t_scn_el **el_arr, long double start_coord[3], t_vec *dir, const long double *range)
{
	t_closest	*closest;
	long double	*t;
	int			i;

	closest = ft_calloc(1, sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	i = 0;
	while (el_arr && el_arr[i])
	{
		t = get_intersection_points(start_coord, dir, el_arr[i]);
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

long double	*get_intersection_points(long double start[3], t_vec *dir, t_scn_el *obj)
{
	long double	quad_param[3];
	long double	d;
	long double	*t;
	t_vec		*CO;

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
	pplane[Z] = cam->coord[Z] + 1;
	return (pplane);
}

t_vec	*get_ray_reflection(t_vec *ray, t_vec *norm)
{
	long double	ray_dot_norm;
	t_vec		*scaled_vec;
	t_vec		*scaled_minus_ray;

	if (!ray || !norm)
		return (NULL);
	ray_dot_norm = 2 * dot(ray, norm);
	scaled_vec = scale(ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}