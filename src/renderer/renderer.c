/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/21 16:44:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <MLX42.h>

void	render_img(t_data *d)
{
	int	x;
	int	x_end;
	int	y;
	int	y_end;

	x = - WIDTH / 2;
	x_end = WIDTH / 2;
	y = - HEIGHT / 2;
	y_end = HEIGHT / 2;
	while (x < x_end)
	{
		while (y < y_end)
		{
			struct v_coord v_coord = canvas_to_viewport(x, y);
			mlx_put_pixel(d.img, i, j, col);
			y++;
		}
		x++;
	}
}
