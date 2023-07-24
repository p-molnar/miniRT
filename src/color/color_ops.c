/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 20:52:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 16:38:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	mix_colors(t_color local_color, t_color reflected_color,
		long double ref_factor)
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

t_color	get_color(t_color color, int channel)
{
	return ((color >> (channel * 8)) & 0xFF);
}

t_color	update_color_channel(t_color curr_color, t_color new_val, int channel)
{
	t_color	col_channel;

	if (new_val < 0)
		new_val = 0;
	else if (new_val > 255)
		new_val = 255;
	col_channel = get_color(curr_color, channel);
	curr_color = curr_color & ~(col_channel << (channel * 8));
	curr_color |= new_val << (channel * 8);
	return (curr_color);
}
