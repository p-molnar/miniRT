/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   axis.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 10:26:30 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 10:26:40 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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