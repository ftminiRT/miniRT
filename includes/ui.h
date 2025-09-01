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
	UIT_EMPTY
}	t_uitype;

typedef struct s_uipt
{
	int x;
	int y;
}	t_uipt;

typedef struct s_uiwin
{
	t_uitype		type;
	struct s_env	*rt;
	struct s_obj	*obj;

}	t_uiwin;

typedef struct s_ui
{
	t_uiwin *stock;
	t_uiwin	*current;

}	t_ui;

#endif