/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 20:50:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:22:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_up_scn_el_ptrs(t_data *d)
{
	d->scn_el[AMB_LIGHT] = get_scn_els(d->scn_el_list, F_AMB_LIGHT);
	d->scn_el[CAM] = get_scn_els(d->scn_el_list, F_CAM | F_TG_CAM);
	d->scn_el[POINT_LIGHT] = get_scn_els(d->scn_el_list, F_POINT_LIGHT);
	d->scn_el[DIR_LIGHT] = get_scn_els(d->scn_el_list, F_DIR_LIGHT);
	d->scn_el[SPHERE] = get_scn_els(d->scn_el_list, F_SPHERE);
	d->scn_el[PLANE] = get_scn_els(d->scn_el_list, F_PLANE);
	d->scn_el[CYLINDER] = get_scn_els(d->scn_el_list, F_CYLINDER);
	d->scn_el[CYLINDER_CAP] = get_scn_els(d->scn_el_list, F_CYLINDER_CAP);
	d->scn_el[ALL_LIGHTS] = get_scn_els(d->scn_el_list,
			F_AMB_LIGHT | F_POINT_LIGHT | F_DIR_LIGHT);
	d->scn_el[ALL_OBJS] = get_scn_els(d->scn_el_list,
			F_SPHERE | F_PLANE | F_CYLINDER);
}
