/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 20:52:46 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/07 12:28:35 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

t_color	mix_colors(t_color c1, t_color c2)
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
	t_color	new_color;

	new_color.r = fmin(intensity * color.r, 255);
	new_color.g = fmin(intensity * color.g, 255);
	new_color.b = fmin(intensity * color.b, 255);
	new_color.a = 255;
	return (new_color);
}
