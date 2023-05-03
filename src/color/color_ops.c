/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 20:52:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 14:10:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
