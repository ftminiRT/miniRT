/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:22:57 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/23 14:23:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

int	clear_mlx(t_env *rt);
void    error_exit(char *msg);
void    rt_mlx_init(t_mlx *mlx);
int     key_pressed(int kc, t_env *e);

#endif