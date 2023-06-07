/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/07 18:02:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_coord3	*get_incident_point(t_coord3 *origin, t_vec3 *dir, t_closest *obj)
{
	t_coord3	*inc_p;

	// origin = get_inv_SRT(origin, obj->el->coord);
	inc_p = offset(origin, scale(obj->dist, dir));
	// if (obj->el->type == CYLINDER)
	// 	inc_p = get_SiRiTi(inc_p, obj->el->coord);
	return (inc_p);
}

void	draw_axes(t_data *data)
{
	int		x;
	int		y;
	t_color	c;

	c = 0xFF0000FF;
	x = 0;
	while (x < CANVAS_W)
	{
		mlx_put_pixel(data->img, x, CANVAS_H / 2, c);
		if (x % 100 == 0)
		{
			mlx_put_pixel(data->img, x, CANVAS_H / 2 - 2, c);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 - 1, c);
			mlx_put_pixel(data->img, x, CANVAS_H / 2, c);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 + 1, c);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 + 2, c);
		}
		x++;
	}
	y = 0;
	while (y < CANVAS_H)
	{
		mlx_put_pixel(data->img, CANVAS_W / 2, y, c);
		if (y % 100 == 0)
		{
			mlx_put_pixel(data->img, CANVAS_W / 2 - 2, y, c);
			mlx_put_pixel(data->img, CANVAS_W / 2 - 1, y, c);
			mlx_put_pixel(data->img, CANVAS_W / 2, y, c);
			mlx_put_pixel(data->img, CANVAS_W / 2 + 1, y, c);
			mlx_put_pixel(data->img, CANVAS_W / 2 + 2, y, c);
		}
		y++;
	}
}


t_closest	*get_closest_el(t_scn_el **el, t_coord3 *origin, t_vec3 *dir, const long double *range)
{
	t_closest	*closest;
	long double	t;
	int			i;

	closest = malloc(sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	i = 0;
	while (el && el[i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(origin, dir, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(origin, dir, el[i]);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(origin, dir, el[i]);
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		i++;
	}
	return (closest);
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