/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/25 17:51:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

long double	*canvas_to_viewport(int x, int y, long double *viewport)
{
	long double	*coord;

	coord = malloc(COORD_SIZE * sizeof(long double));
	if (!coord)
		error(ft_strdup("Malloc error\n"), EXIT, 1);
	coord[X] = x * viewport[X] / CANVAS_W;
	coord[Y] = y * viewport[Y] / CANVAS_H;
	return (coord);
}

long double	*get_intersection_points(long double *cam_position,
		long double *proj_plane, t_scn_el *obj)
{
	long double	r;
	t_vec		*CO;
	t_vec		*D;
	long double	a;
	long double	b;
	long double	c;
	long double	discriminant;
	long double	*arr;

	r = obj->diameter / 2;
	CO = get_dir_vec(cam_position, obj->coord);
	D = get_dir_vec(cam_position, proj_plane);
	a = dot(D, D);
	b = 2.0 * dot(CO, D);
	c = dot(CO, CO) - r * r;
	discriminant = b * b - 4 * a * c;
	arr = malloc(2 * sizeof(long double));
	arr[0] = INF;
	arr[1] = INF;
	if (discriminant >= 0)
	{
		arr[0] = (-b + sqrt(discriminant)) / (2.0 * a);
		arr[1] = (-b - sqrt(discriminant)) / (2.0 * a);
	}
	return (arr);
}

t_color	trace_ray(t_data *data, long double *cam_pos, long double *proj_plane,
		long double min, long double max)
{
	t_scn_el	*closest_el;
	t_scn_el	**spheres;
	long double	closest_t;
	long double	*t;
	int			i;
	int			bgclr;

	bgclr = 0xFFFFFFFF;
	closest_t = INF;
	closest_el = NULL;
	spheres = get_scn_els(data->scn_el, SPHERE);
	i = 0;
	while (spheres && spheres[i])
	{
		t = get_intersection_points(cam_pos, proj_plane, spheres[i]);
		// printf("t_1: %Lf, t_2: %Lf\n", t[0], t[1]);
		if (t[0] >= min && t[0] <= max && t[0] < closest_t)
		{
			closest_t = t[0];
			closest_el = spheres[i];
		}
		if (t[1] >= min && t[1] <= max && t[1] < closest_t)
		{
			closest_t = t[1];
			closest_el = spheres[i];
		}
		i++;
	}
	free(spheres);
	if (closest_el == NULL)
		return (bgclr);
	else
	{
		// printf("something?\n");
		return (closest_el->color);
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
	int			x;
	int			y;
	t_color		color;
	long double	*vp_coord;
	t_scn_el	**cam;

	cam = get_scn_els(data->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found"), EXIT, 1);
	x = -CANVAS_W / 2;
	while (x < CANVAS_W / 2)
	{
		y = -CANVAS_H / 2;
		while (y < CANVAS_H / 2)
		{
			vp_coord = canvas_to_viewport(x, y, data->viewport);
			// printf("x: %Lf, y: %Lf\n",vp_coord[X], vp_coord[Y]);
			color = trace_ray(data, cam[0]->coord, vp_coord, 1, INF);
			mlx_put_pixel(data->img, x + CANVAS_W / 2, y + CANVAS_H / 2, color);
			free(vp_coord);
			y++;
		}
		x++;
	}
	draw_axes(data);
	free(cam);
}
