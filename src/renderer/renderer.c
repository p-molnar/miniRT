/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/08 00:40:55 by pmolnar       ########   odam.nl         */
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
	ray_dot_norm = 2 * dot(ray, norm);
	scaled_vec = scale(ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}

t_vec	*get_incident_point(long double *start_coord, t_vec *direction,
		long double distance)
{
	t_vec	*O;
	t_vec	*scaled_dir;
	t_vec	*incident_point;

	O = create_vec(start_coord, start_coord);
	scaled_dir = scale(distance, direction);
	incident_point = add(O, scaled_dir);
	free(O);
	free(scaled_dir);
	return (incident_point);
}

t_color	get_reflected_color(t_data *data, t_vec *dir, const long double *range, int depth)
{
	t_color	reflected_color;

	data->vec[Dneg] = scale(-1, dir);
	data->vec[Rv] = get_ray_reflection(data->vec[Dneg], data->vec[N]);
	reflected_color = trace_ray(data, data->vec[P]->coord, data->vec[Rv], range, depth - 1);
	return (reflected_color);
}

t_color	mix_colors(t_color local_color, t_color reflected_color, long double ref_factor)
{
	t_color	color;
	t_color	c1;
	t_color	c2;
	int		i;

	color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		c1 = get_color(local_color, i) * (1 - ref_factor);
		c2 = get_color(reflected_color, i) * ref_factor;
		color = update_color_channel(color, c1 + c2, i);
		i++;
	}
	return (color);
}

t_color	trace_ray(t_data *data, long double *start_coord, t_vec *dir,
		const long double *range, int recursion_depth)
{
	t_closest			*closest;
	t_scn_el			**el_arr;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {0.001, INF};

	el_arr = get_scn_els(data->scn_el, SPHERE);
	closest = get_closest_el(el_arr, start_coord, dir, range);
	if (!closest || !closest->el)
		return (BACKGROUND_COLOR);
	data->vec[P] = get_incident_point(start_coord, dir, closest->dist);
	data->vec[N] = create_vec(closest->el->coord, data->vec[P]->coord);
	normalize_vec(data->vec[N]);
	color[0] = get_incident_point_color(data, closest->el);
	ref_factor = closest->el->reflection;
	free(closest);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (color[0]);
	color[1] = get_reflected_color(data, dir, ref_range, recursion_depth);
	return (mix_colors(color[0], color[1], ref_factor));
}

long double	*get_rotation_mx(long double theta, t_vec *axis)
{
	long double	sin_t;
	long double	cos_t;
	long double	*u;
	long double	*mx;

	sin_t = sin(deg_to_rad(theta));
	cos_t = cos(deg_to_rad(theta));
	u = axis->n_coord;
	mx = malloc(9 * sizeof(long double));
	mx[0] = cos_t + pow(u[0], 2) * (1 - cos_t);
	mx[1] = u[0] * u[1] * (1 - cos_t) - u[2] * sin_t;
	mx[2] = u[0] * u[2] * (1 - cos_t) + u[1] * sin_t;
	mx[3] = u[1] * u[0] * (1 - cos_t) + u[2] * sin_t;
	mx[4] = cos_t + pow(u[1], 2) * (1 - cos_t);
	mx[5] = u[1] * u[2] * (1 - cos_t) - u[0] * sin_t;
	mx[6] = u[2] * u[0] * (1 - cos_t) - u[1] * sin_t;
	mx[7] = u[2] * u[1] * (1 - cos_t) + u[0] * sin_t;
	mx[8] = cos_t + pow(u[2], 2) * (1 - cos_t);
	return (mx);
}

void	render_img(t_data *data)
{
	int					canvas[2];
	int					screen[2];
	t_color				color;
	long double			*pplane_coord;
	const long double	range[RANGE_SIZE] = {1, INF};

	long double z_axis[3] = {0, 0, 1};

	t_vec	*z= create_vec(NULL, z_axis);
	long double angle = rad_to_deg(acos(dot(z, data->cam->n_vec) / (z->len * data->cam->n_vec->len)));
	t_vec	*rot_axis = cross(z, data->cam->n_vec);
	long double *mx = get_rotation_mx(angle, rot_axis);
	for (int i = 0; i < 9; i++)
		printf("%Lf\n", mx[i]);
	printf("ra: %Lf;%Lf;%Lf\n", rot_axis->coord[0], rot_axis->coord[1], rot_axis->coord[2]);
	canvas[X] = -CANVAS_W / 2;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			init_vec(data->vec, VEC_SIZE);
			pplane_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport);
			data->vec[D] = create_vec(data->cam->coord, pplane_coord);
			if (canvas[X] == 0 && canvas[Y] == 0)
				printf("%Lf; %Lf; %Lf\n", data->vec[D]->coord[0], data->vec[D]->coord[1], data->vec[D]->coord[2]);
			data->vec[D] = product(mx, data->vec[D]);
			if (canvas[X] == 0 && canvas[Y] == 0)
				printf("%Lf; %Lf; %Lf\n", data->vec[D]->coord[0], data->vec[D]->coord[1], data->vec[D]->coord[2]);
			color = trace_ray(data, data->cam->coord, data->vec[D], range, 0);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			free_vec(data->vec, VEC_SIZE);
			free(pplane_coord);
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
}
