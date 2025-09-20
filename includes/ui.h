/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:22:52 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/09 15:22:35 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "minirt.h"
# include "vec3.h"

# define UI_WIDTH 200
# define UI_HEIGHT 500
# define UI_CS_WIDTH 2
# define UI_CS_HEIGHT 5
# define STEP_COL 50
# define STEP_POS 5
# define STEP_SPOS 25
# define STEP_ROT 15
# define STEP_CAMROT 5
# define STEP_SH 2
# define STEP_RF 0.1
# define STEP_RAY 2
# define STEP_HEI 5
# define STEP_MAX 1
# define STEP_BIGRAY 5
# define STEP_RING 2
# define STEP_BRI 0.1
# define STEP_FOV 10

typedef enum e_itm_type
{
	UIT_SCL_BTN,
	UIT_COL_BTN,
	UIT_SH_BTN,
	UIT_FOV_BTN,
	UIT_01_BTN,
	UIT_ROT_BTN,
	UIT_MV_BTN,
	UIT_EVNT_BTN,
	UIT_SLDR,
	UIT_EXPORT_BTN,
	UIT_SPOT_BTN,
	UIT_CAM_BTN,
	UIT_RND_BTN,
	UIT_SEL_BTN,
	UIT_DFT_PANE
}					t_itm_type;

typedef struct s_uipt
{
	int				x;
	int				y;
}					t_uipt;

typedef struct s_scl_btn
{
	double			*value;
	double			factor;
	t_vec3			v;
}					t_scl_btn;

typedef struct s_btn_data
{
	void			*value;
	double			factor;
	t_vec3			v;
	t_itm_type		type;
}					t_btn_data;

typedef struct s_items
{
	t_itm_type		type;
	t_uipt			pos;
	t_uipt			scale;
	t_scl_btn		btn;
	void			(*function)(void *rt);
	struct s_items	*next;
}					t_items;

typedef struct s_uipane
{
	size_t			type;
	struct s_obj	*obj;
	struct s_cam	*cam;
	struct s_light	*light;
	t_items			*itms;
	struct s_uipane	*next;
}					t_uipane;

typedef int			(*t_build_pane[OBJTYPENUMBER + 1])(void *, t_uipane *);
typedef int			(*t_fill_values[OBJTYPENUMBER + 1])(void *, t_uipane *);

typedef struct s_ui
{
	t_uipane		*stock;
	t_uipane		*current;
	t_items			*dft_itms;
	t_build_pane	build_pane;
	t_fill_values	fill_values;
	void			*pane_img[OBJTYPENUMBER];

}					t_ui;

#endif