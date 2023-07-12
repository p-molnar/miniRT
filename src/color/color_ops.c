/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 20:52:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/12 13:01:17by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	get_rgba(int r, int g, int b, int a)
{
	t_color	color;

	color.color = r << 24 | g << 16 | b << 8 | a;
	return (color);
}

t_color	get_color(t_color color, int channel)
{
	t_color	col;

	col.color = (color.color >> (channel * 8)) & 0xFF;
	return (col);
}

t_color	update_color_channel(t_color curr_color, t_color new_val, int channel)
{
	int	color_channel;

	if (new_val.color < 0)
		new_val.color = 0;
	else if (new_val.color > 255)
		new_val.color = 255;
	color_channel = get_color(curr_color, channel).color;
	curr_color.color = curr_color.color & ~(color_channel << (channel * 8));
	curr_color.color |= new_val.color << (channel * 8);
	return (curr_color);
}

void	normalize_color(t_color color)
{
	color.r = color.r / 255;
	color.g = color.g / 255;
	color.b = color.b / 255;
	color.a = color.a / 255;
}

void	denormalize_color(t_color color)
{
	color.r = color.r * 255;
	color.g = color.g * 255;
	color.b = color.b * 255;
	color.a = color.a * 255;
}
