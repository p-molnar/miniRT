/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:44:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/18 23:03:11 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

t_closest	*cast_shadow(t_data *data, long double *range)
{
	t_closest	*closest_el;
	t_scn_el **scn_els;

	scn_els = get_scn_els(data->scn_el, G_OBJS);
	closest_el = get_closest_el(data, scn_els, data->vec[P]->coord, data->vec[L], range);
	// if (closest_el->el)
		// printf("shadow: el: %d\n", closest_el->el->type);
	return (closest_el);
}
