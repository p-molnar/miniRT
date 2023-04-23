/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/21 21:28:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <MLX42.h>

t_coord_2d	*canvas_to_viewport(int x, int y);
{
	t_coord_2d	*coord;

	coord = malloc(sizeof(t_coord_2d));
	if (!coord_2d)
		error(ft_strdup("Malloc error\n"), EXIT, 1);
	coord->x = x * VIEWPORT_W/WIDTH;
	coord->y = y * VIEWPORT_H/HEIGHT;
	return (coord);
}

void	render_img(t_data *d)
{
	int			x;
	int			y;
	t_coord_2d	*v_coord;

	x = - WIDTH / 2;
	y = - HEIGHT / 2;
	while (x < WIDTH / 2)
	{
		while (y < HEIGHT / 2)
		{
			v_coord = canvas_to_viewport(x, y);
			// mlx_put_pixel(d.img, , j, col);
			y++;
		}
		x++;
	}
}
