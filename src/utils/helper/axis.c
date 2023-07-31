/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   axis.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 10:26:30 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/28 17:28:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	draw_axes(t_data *data)
{
	int		x;
	int		y;
	t_color	c;

	c.color = 0xFF0000FF;
	x = 0;
	while (x < CANVAS_W)
	{
		mlx_put_pixel(data->img, x, CANVAS_H / 2, c.color);
		if (x % 100 == 0)
		{
			mlx_put_pixel(data->img, x, CANVAS_H / 2 - 2, c.color);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 - 1, c.color);
			mlx_put_pixel(data->img, x, CANVAS_H / 2, c.color);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 + 1, c.color);
			mlx_put_pixel(data->img, x, CANVAS_H / 2 + 2, c.color);
		}
		x++;
	}
	y = 0;
	while (y < CANVAS_H)
	{
		mlx_put_pixel(data->img, CANVAS_W / 2, y, c.color);
		if (y % 100 == 0)
		{
			mlx_put_pixel(data->img, CANVAS_W / 2 - 2, y, c.color);
			mlx_put_pixel(data->img, CANVAS_W / 2 - 1, y, c.color);
			mlx_put_pixel(data->img, CANVAS_W / 2, y, c.color);
			mlx_put_pixel(data->img, CANVAS_W / 2 + 1, y, c.color);
			mlx_put_pixel(data->img, CANVAS_W / 2 + 2, y, c.color);
		}
		y++;
	}
}