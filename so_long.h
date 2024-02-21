/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:56:03 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/11/30 16:56:05 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct {
	char **map;
	int rows;
	int cols;
} Map;

typedef struct {
	void *img;
	int width;
	int height;
} Texture;

int	move(int keycode, t_vars *vars);
void	mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color);
void	draw_map(void *mlx, void *win, Map *map, Texture *wall_texture, Texture *user_texture, Texture *coin, Texture *salida);
Texture	load_texture(void *mlx, char *file_path);

#endif
