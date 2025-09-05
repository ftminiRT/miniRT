/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-01 10:22:52 by tcoeffet          #+#    #+#             */
/*   Updated: 2025-09-01 10:22:52 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
#define UI_H

# include "minirt.h"
# include "structs.h"

# define UI_WIDTH 200
# define UI_HEIGHT 500
# define UI_CS_WIDTH 2
# define UI_CS HEIGHT 5

typedef enum e_uitype
{
	UIT_CAM,
	UIT_AMB,
	UIT_SPOT,
	UIT_SPH,
	UIT_PLAN,
	UIT_CYL,
	UIT_CONE,
	UIT_TORE,
	UIT_HYP,
	UIT_PARA,
	UIT_TRIANGLE,
	UIT_MOEB,
	UIT_DEFAULT
}	t_uitype;

typedef enum e_itm_type
{
	UIT_SCL_BTN,
	UIT_EVNT_BTN,
	UIT_SLDR
}	t_itm_type;

typedef struct s_uipt
{
	int x;
	int y;
}	t_uipt;

typedef struct s_scl_btn
{
	double			*value;
	double			factor;
}	t_scl_btn;

typedef struct s_dp_list
{
	void				*img;
	size_t				width;
	size_t				height;
	t_uipt				pos;
	struct s_dp_list	*next;
}	t_dp_list;

typedef struct s_items
{
	t_itm_type		type;
	t_uipt			pos;
	t_uipt			scale;
	t_scl_btn		btn;
	void			(*function)(t_env *);
	struct s_items	*next;
}	t_items;

typedef struct s_uipane
{
	t_uitype		type;
	struct s_obj	*obj;
	struct s_cam	*cam;
	struct s_light	*light;
	t_items			*itms;
	t_dp_list		*dplist;
	struct s_uipane	*next;
}	t_uipane;

typedef struct s_ui
{
	t_uipane	*stock;
	t_uipane	*current;
	t_items 	*dft_itms;
	int		(*build_pane[OBJTYPENUMBER])(t_env *rt, t_uipane *current);

}	t_ui;

#endif