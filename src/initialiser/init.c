/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/07 18:01:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
void	print_mx(t_mx *mx)
{
	printf("[\n");
	int dim = mx->r * mx->c;
	for (int i = 0; i < dim; i++)
	{
		printf("% .4Lf   ", mx->m[i]);
		if (!((i + 1) % mx->c))
			printf("\n");
	}
	printf("]\n");
}

void	setup_camera(t_data	*d)
{
	t_vec3	*right_vec;
	t_vec3	*fw_vec;
	t_vec3	*up_vec;
	t_vec3	*def_up_vec;

	def_up_vec = create_vec(NULL, create_coord(0, 1, 0));
	if (d->cam->type == F_CAM)
		fw_vec = d->cam->n_vec;
	else
	{
		fw_vec = create_vec(d->cam->coord, d->cam->tg_coord);
		normalize(fw_vec);
	}
	if (fw_vec->dir[X] == 0 && fw_vec->dir[Y] == 0 && fw_vec->dir[Z] == 0)
	{
		fw_vec->dir[Z] = 1;
		fw_vec->len = 1;
	}
	else if ((fw_vec->dir[X] == 0 && fw_vec->dir[Z] == 0) && (fw_vec->dir[Y] == -1 || fw_vec->dir[Y] == 1))
	{
		def_up_vec->dir[Y] = 0;
		def_up_vec->dir[Z] = 1;
		fw_vec->len = 1;
	}
	right_vec = cross(def_up_vec, fw_vec);
	normalize(right_vec);
    up_vec = cross(fw_vec, right_vec);
	normalize(up_vec);
	printf("forward: %Lf, %Lf, %Lf\n", fw_vec->dir[X],
			fw_vec->dir[Y], fw_vec->dir[Z]);
	printf("right: %Lf, %Lf, %Lf\n", right_vec->dir[0],
			right_vec->dir[1], right_vec->dir[2]);
	printf("up: %Lf, %Lf, %Lf\n", up_vec->dir[0],
			up_vec->dir[1], up_vec->dir[2]);
	
	d->ctw_mx = malloc(sizeof(t_mx));
	d->ctw_mx->r = 4;
	d->ctw_mx->c = 4;
	d->ctw_mx->m = ft_calloc(16, sizeof(long double));
	d->ctw_mx->m[0] = right_vec->dir[X];
	d->ctw_mx->m[1] = up_vec->dir[X];
	d->ctw_mx->m[2] = fw_vec->dir[X];
	d->ctw_mx->m[3] = d->cam->coord[X];

	d->ctw_mx->m[4] = right_vec->dir[Y];
	d->ctw_mx->m[5] = up_vec->dir[Y];
	d->ctw_mx->m[6] = fw_vec->dir[Y];
	d->ctw_mx->m[7] = d->cam->coord[Y];

	d->ctw_mx->m[8] = right_vec->dir[Z];
	d->ctw_mx->m[9] = up_vec->dir[Z];
	d->ctw_mx->m[10] = fw_vec->dir[Z];
	d->ctw_mx->m[11] = d->cam->coord[Z];
	d->ctw_mx->m[15] = 1;
	print_mx(d->ctw_mx);
}

void	set_up_scene(t_data *data)
{
	t_list *ptr;
	t_scn_el *obj;
	t_scn_el **cam;

	ptr = data->all_scn_el;
	while (ptr)
	{
		obj = ptr->content;
		obj->radius = obj->diameter / 2;
		ptr = ptr->next;
	}
	cam = get_scn_els(data->all_scn_el, F_CAM | F_TG_CAM);
	if (cam)
		data->cam = cam[0];
	setup_camera(data);
}