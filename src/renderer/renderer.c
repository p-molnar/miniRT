/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/24 23:56:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdlib.h>
#include <stdio.h>

double	*canvas_to_viewport(int x, int y, double d)
{
	double	*coord;

	coord = malloc(COORD_SIZE * sizeof(double));
	if (!coord)
		error(ft_strdup("Malloc error\n"), EXIT, 1);
	coord[X] = x * VIEWPORT_W / WIDTH;
	coord[Y] = y * VIEWPORT_H / HEIGHT;
	coord[Z] = d;
	return (coord);
}

double	*get_intersection_points(double *cam_position, double *proj_plane,
		t_scn_el *obj)
{
	double	r;
	t_vec	*CO;
	t_vec	*D;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	*arr;

	r = obj->diameter / 2;
	CO = get_dir_vec(cam_position, obj->coord);
	D = get_dir_vec(cam_position, proj_plane);
	a = dot(D, D);
	b = 2 * dot(CO, D);
	c = dot(CO, CO) - r * r;
	discriminant = b * b - 4 * a * c;
	arr = malloc(2 * sizeof(double));
	if (discriminant < 0)
	{
		arr[0] = INF;
		arr[1] = INF;
	}
	else
	{
		arr[0] = (-b + sqrt(discriminant)) / (2 * a);
		arr[1] = (-b - sqrt(discriminant)) / (2 * a);
	}
	return (arr);
}

t_color	trace_ray(t_data *data, double *cam_pos, double *proj_plane,
		int min, int max)
{
	t_scn_el		*closest_el;
	t_scn_el		**spheres;
	int				closest_t;
	double			*t;
	int				i;
	int				bgclr;

	bgclr = get_rgba(173, 11, 173, 1);
	closest_t = INF;
	closest_el = NULL;
	spheres = get_scn_els(data->scn_el, SPHERE);
	i = 0;
	while (spheres && spheres[i])
	{
		t = get_intersection_points(cam_pos, proj_plane, spheres[i]);
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
	// free_arr((void **)spheres);
	if (closest_el == NULL)
		return (bgclr);
	else
	{
		// printf("closes col: %d\n", closest_el->color);
		// printf("closes col: %d\n", closest_el->type);
		return (closest_el->color);
	}
}

void	render_img(t_data *data)
{
	int			x;
	int			y;
	t_color		color;
	double		*vp_coord;
	t_scn_el	**cam;

	cam = get_scn_els(data->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found"), EXIT, 1);
	x = -WIDTH / 2;
	y = -HEIGHT / 2;
	while (x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y < HEIGHT / 2)
		{
			vp_coord = canvas_to_viewport(x, y, 1);
			color = trace_ray(data, cam[0]->coord, vp_coord, 1, INF);
			// printf("x: %d, y: %d\n", 0xFF0000FF, x);
			mlx_put_pixel(data->img, x + 250, y + 250, color);
			y++;
		}
		x++;
	}
}
