/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:38 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/05 15:48:44 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_make_map(t_game *game, int fd)
{
	char	*gnl;
	int		rows;
	int		cols;
	int		i;

	rows = 0;
	cols = 0;
	i = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		rows++;
		cols = (ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	game->rows = rows;
	game->cols = cols;
	game->map = (char **)malloc(sizeof(char *) * rows + 1);
	while (gnl != NULL)
	{
		game->map[i] = gnl;
		i++;
	}
	close(fd);
}


//Funcion para cargar el mapa en la estructura
void	ft_charge_map(t_game *game)
{
	printf("Funcion_charge_map\n");
	int			px;

	px = 50;
	game->wall.height = 50;
	game->wall.width = 50;
	printf("pointer wall h: %p\n", &game->wall.height);
	printf("pointer wall w: %p\n", &game->wall.width);
	load_texture(game->mlx, "texturas/bloque.xpm");
}

void	ft_draw_map(t_game *game, t_sprite *wall)
{
	int		i;
	int		j;
	int		block_size;

	block_size = 50;
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, wall->img, j * block_size, i * block_size);
			j++;
		}
		i++;
	}
}


