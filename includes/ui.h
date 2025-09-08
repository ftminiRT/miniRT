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

typedef struct s_items
{
	t_itm_type		type;
	t_uipt			pos;
	t_uipt			scale;
	t_scl_btn		btn;
	void			(*function)(void *rt);
	struct s_items	*next;
}	t_items;

typedef struct s_uipane
{
	t_objtype		type;
	struct s_obj	*obj;
	struct s_cam	*cam;
	struct s_light	*light;
	t_items			*itms;
	struct s_uipane	*next;
}	t_uipane;

typedef struct s_ui
{
	t_uipane	*stock;
	t_uipane	*current;
	t_items 	*dft_itms;
	int		(*build_pane[OBJTYPENUMBER])(void *rt, t_uipane *current);
	void	*pane_img[OBJTYPENUMBER];

}	t_ui;

#endif