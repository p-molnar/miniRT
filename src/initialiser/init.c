/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 20:50:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/24 21:00:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>

void	populate_window_properties(t_data *d)
{
	d->window.width = CANVAS_W;
	d->window.height = CANVAS_H;
}

void	set_up_scn_el_ptrs(t_data *d)
{
	d->scn_els[AMB_LIGHT] = get_scn_els(d->all_scn_el, F_AMB_LIGHT);
	d->scn_els[CAM] = get_scn_els(d->all_scn_el, F_CAM | F_TG_CAM);
	d->scn_els[POINT_LIGHT] = get_scn_els(d->all_scn_el, F_POINT_LIGHT);
	d->scn_els[DIR_LIGHT] = get_scn_els(d->all_scn_el, F_DIR_LIGHT);
	d->scn_els[SPHERE] = get_scn_els(d->all_scn_el, F_SPHERE);
	d->scn_els[PLANE] = get_scn_els(d->all_scn_el, F_PLANE);
	d->scn_els[CYLINDER] = get_scn_els(d->all_scn_el, F_CYLINDER);
	d->scn_els[CYLINDER_CAP] = get_scn_els(d->all_scn_el, F_CYLINDER_CAP);
	d->scn_els[ALL_LIGHTS] = get_scn_els(d->all_scn_el, G_LIGHTS);
	d->scn_els[ALL_OBJS] = get_scn_els(d->all_scn_el, G_OBJS);
}
