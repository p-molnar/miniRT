/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/11 11:49:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_vec3	*get_incident_point(long double *start_coord, t_vec3 *direction,
		long double distance)
{
	t_vec3	*O;
	t_vec3	*scaled_dir;
	t_vec3	*incident_point;

	// O = create_vec(start_coord, start_coord);
	O = create_vec(NULL, start_coord);
	scaled_dir = scale(distance, direction);
	incident_point = add(O, scaled_dir);
	free(O);
	free(scaled_dir);
	return (incident_point);
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


t_closest	*get_closest_el(t_data *data, t_scn_el **el_arr, long double start_coord[3], t_vec3 *dir, const long double *range)
{
	t_closest	*closest;
	long double	*t;
	int			i;

	// (void) start_coord, (void) dir;
	closest = ft_calloc(1, sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	t = NULL;
	i = 0;
	while (el_arr && el_arr[i])
	{
		if (el_arr[i]->type == SPHERE)
			t = get_sphere_intersections(start_coord, dir, el_arr[i]);
		else if (el_arr[i]->type == CYLINDER)
			t = get_cylinder_intersection(data, start_coord, el_arr[i]);
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
	// free(t);
	// if (closest->el && closest->el->type == CYLINDER)
	// 		// printf("%Lf, %Lf, %Lf\n", dir->coord[X], dir->coord[Y], dir->coord[Z]);
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