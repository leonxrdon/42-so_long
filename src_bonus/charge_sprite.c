/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:28:30 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/11 13:28:38 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	ft_load_texture(void *mlx, char *file_path)
{
	t_sprite	txre;
	char		*route;

	route = ft_strjoin(XPM_ROUTE, file_path);
	txre.height = BK_SIZE;
	txre.width = BK_SIZE;
	txre.img = mlx_xpm_file_to_image(mlx, route, &txre.width, &txre.height);
	ft_errors((txre.img == NULL), "Error:\nNo se pudo cargar la textura");
	free(route);
	return (txre);
}

void	ft_load_extras(t_game *game)
{
	int			i;
	char		*path;
	t_sprite	wall;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = ft_build_path("wall_", i);
		wall = ft_load_texture(game->mlx, path);
		game->wall[i] = wall;
		free(path);
		i++;
	}
	game->collectible = ft_load_texture(game->mlx, "ball_1.xpm");
	game->exit = ft_load_texture(game->mlx, "exit.xpm");
	game->floor = ft_load_texture(game->mlx, "floor.xpm");
}

void	ft_charge_sprite(t_game *game, char	*file_path)
{
	char		*gnl;
	int			i;
	int			fd;

	fd = open(file_path, O_RDONLY);
	ft_errors((fd < 0), "Error:\nEl Archivo no existe o se se puede abrir");
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->map[i] = *ft_split(gnl, '\n');
		free(gnl);
		gnl = get_next_line(fd);
		i++;
	}
	game->player.action = "front";
	ft_load_extras(game);
	ft_load_player(game);
	ft_draw_map(game);
}

void	ft_charge_wall(t_game *game, int i, int j)
{
	int	random;

	random = (i + j) % NUM_FRAMES;
	if (random >= NUM_FRAMES)
		random = 0;
	mlx_put_image_to_window(game->mlx, game->win,
		game->wall[random].img,
		j * BK_SIZE,
		i * BK_SIZE);
}
