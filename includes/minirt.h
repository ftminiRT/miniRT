/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:56 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/09/04 23:18:39 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef WIDTH
#  define WIDTH 700
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# define EPSILON 1e-6
# define MAX_DEPTH 5
# define BONUS 1
# define OBJTYPENUMBER 9

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "keycodes.h"
# include "proto.h"
# include "libft.h"

#endif