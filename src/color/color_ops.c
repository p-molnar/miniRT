/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 20:52:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/30 02:10:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

t_color	mix_colors(uint32_t local_color, uint32_t reflected_color,
		long double ref_factor)
{
	t_color		color;
	uint32_t	c1;
	uint32_t	c2;
	int			i;

	color.color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		c1 = get_color(local_color, i).color * (1 - ref_factor);
		c2 = get_color(reflected_color, i).color * ref_factor;
		color.color = update_color_channel(color.color, c1 + c2, i);
		i++;
	}
	return (color);
}

t_color	get_color(uint32_t color, int channel)
{
	t_color	new_color;

	new_color.color = color >> (channel * 8) & 0xFF;
	return (new_color);
}

uint32_t	update_color_channel(uint32_t curr_color, uint32_t new_val, int channel)
{
	uint32_t	col_channel;

	if (new_val < 0)
		new_val = 0;
	else if (new_val > 255)
		new_val = 255;
	col_channel = get_color(curr_color, channel).color;
	curr_color = curr_color & ~(col_channel << (channel * 8));
	curr_color |= new_val << (channel * 8);
	return (curr_color);
}

t_color	mix_colors2(t_color c1, t_color c2)
{
	t_color	mixed_color;

	mixed_color.r = 255 * (c1.r / 255.0 * c2.r / 255.0);
	mixed_color.g = 255 * (c1.g / 255.0 * c2.g / 255.0);
	mixed_color.b = 255 * (c1.b / 255.0 * c2.b / 255.0);
	mixed_color.a = 255;
	return (mixed_color);
}

t_color	sum_colors(t_color c1, t_color c2)
{
	t_color	new_color;

	new_color.r = fmin(c1.r + c2.r, 255);
	new_color.g = fmin(c1.g + c2.g, 255);
	new_color.b = fmin(c1.b + c2.b, 255);
	new_color.a = 255;
	return (new_color);
}

t_color	intensify_color(long double intensity, t_color color)
{
	color.r = fmin(intensity * color.r, 255);
	color.g = fmin(intensity * color.g, 255);
	color.b = fmin(intensity * color.b, 255);

	return (color);
}
