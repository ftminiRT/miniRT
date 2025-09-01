/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:56 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/08/28 19:08:13 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "structs.h"
# include "keycodes.h"
# include "proto.h"
# include "libft.h"
# include "ui.h"

# ifndef WIDTH
#  define WIDTH 700
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# define EPSILON 1e-6

#endif