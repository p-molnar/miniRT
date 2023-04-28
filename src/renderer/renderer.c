/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/28 16:33:31 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

#define CO 0
#define D 1

long double	*canvas_to_viewport(int x, int y, long double *viewport)
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

long double	*get_intersection_points(long double *cam_position,
										long double *proj_plane,
										t_scn_el *obj)
{
	long double	r;
	t_vec		*vec[2];
	long double	param[3];
	long double	discriminant;
	long double	*t;

	r = obj->diameter / 2;
	vec[CO] = create_vec(obj->coord, cam_position);
	vec[D] = create_vec(cam_position, proj_plane);
	param[0] = dot(vec[D], vec[D]);
	param[1] = 2.0 * dot(vec[CO], vec[D]);
	param[2] = dot(vec[CO], vec[CO]) - r * r;
	t = quad_eq_solver(param[0], param[1], param[2], &discriminant);
	if (discriminant < 0)
	{
		t = malloc(2 * sizeof(long double));
		if (!t)
			return (NULL);
		t[0] = INF;
		t[1] = INF;
	}
	free(vec[CO]);
	free(vec[D]);
	return (t);
}

t_scn_el	*get_closest_el(long double *cam_coord, long double *pplane_coord,
		t_scn_el *sphere, long double *closest_t)
{
	long double	*t;
	t_scn_el	*closest_el;

	closest_el = NULL;
	t = get_intersection_points(cam_coord, pplane_coord, sphere);
	if (is_in_range_f(t[0], 1, INF) && t[0] < *closest_t)
	{
		*closest_t = t[0];
		closest_el = sphere;
	}
	if (is_in_range_f(t[1], 1, INF) && t[1] < *closest_t)
	{
		*closest_t = t[1];
		closest_el = sphere;
	}
	// free(t);
	return (closest_el);
}

int	get_color(t_data *data, t_scn_el *closest_el, t_vec *P, t_vec *N)
{
	t_color		new_color;
	t_color		col;
	int			i;

	i = 0;
	while (i < 4)
	{
		col = ((closest_el->color >> (i * 8)) & 0xFF)
			* compute_lighting_intensity(data, P->coord, N);
		new_color = new_color | col << (i * 8);
		i++;
	}
	return (new_color);
}

t_color	trace_ray(t_data *data, long double *cam_coord,
		long double *pplane_coord)
{
	t_scn_el	*closest_el;
	long double	closest_t;
	t_scn_el	**spheres;
	t_vec		*vec[PARAM_SIZE];
	int			i;

	closest_t = INF;
	closest_el = NULL;
	spheres = get_scn_els(data->scn_el, SPHERE);
	i = 0;
	while (spheres && spheres[i])
		closest_el = get_closest_el(cam_coord, pplane_coord,
				spheres[i++], &closest_t);
	free(spheres);
	if (closest_el == NULL)
		return (data->bg);
	else
	{
		vec[D] = create_vec(cam_coord, pplane_coord);
		vec[O] = create_vec(cam_coord, cam_coord);
		scale(closest_t, vec[D]);
		vec[P] = add(vec[O], vec[D]);
		vec[N] = create_vec(vec[P]->coord, closest_el->coord);
		return (get_color(data, closest_el, vec[P], vec[N]));
	}
}

void	draw_axes(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < CANVAS_W)
	{
		y = 0;
		while (y < CANVAS_H)
		{
			if (y % ((CANVAS_H / 2) - 1) == 0 || x % ((CANVAS_W / 2) - 1) == 0)
				mlx_put_pixel(data->img, x, y, 0xFF1200FF);
			y++;
		}
		x++;
	}
}

void	render_img(t_data *data)
{
	int			coord[COORD_SIZE];
	t_color		color;
	long double	*vp_coord;
	t_scn_el	**cam;

	cam = get_scn_els(data->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found"), EXIT, 1);
	coord[X] = -CANVAS_W / 2;
	while (coord[X] < CANVAS_W / 2)
	{
		coord[Y] = CANVAS_H / 2;
		while (coord[Y] > -CANVAS_H / 2)
		{
			vp_coord = canvas_to_viewport(coord[X], coord[Y], data->viewport);
			color = trace_ray(data, cam[0]->coord, vp_coord);
			mlx_put_pixel(data->img, coord[X] + CANVAS_W / 2, CANVAS_H / 2
					- coord[Y], color);
			free(vp_coord);
			coord[Y]--;
		}
		coord[X]++;
	}
	draw_axes(data);
	free(cam);
}
