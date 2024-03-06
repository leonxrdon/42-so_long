/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:18:22 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/07/12 18:18:27 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_sprite	load_texture(void *mlx, char *file_path)
{
	t_sprite	texture;
	char	*route;

	route = ft_strjoin(XPM_ROUTE, file_path);
	texture.height = 50;
	texture.width = 50;
	texture.path = route;
	texture.img = mlx_xpm_file_to_image(mlx, route, &texture.width, &texture.height);
	if (!texture.img)
	{
		printf("Error al cargar la textura desde %s\n", route);
		exit(1);
	}
	return (texture);
}

void	ft_game_init(t_game *game, int fd, char *file_path)
{
	game->mlx = mlx_init();
	ft_make_map(game, fd);
	game->win = mlx_new_window(game->mlx, (game->cols * 50), (game->rows * 50), "so_long");
	ft_charge_map(game, file_path);

	mlx_key_hook(game->win, ft_move, game);
	mlx_loop(game->mlx);
}

void	ft_update_frames(t_player *player)
{
	player->frame = (player->frame + 1) % NUM_FRAMES;
	printf("frame: %d\n", player->frame);
}
//funcion para validar la extencion del argumento
int	main(int argc, char **argv) {
	t_game	game;
	int		fd;

	if (argc != 2)
		return (0);
	if (argv[0] != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE);
		if (ft_validate_ext(argv[1], ".ber"))
		{
			printf("Error: El archivo no tiene la extencion .ber\n");
			exit(EXIT_FAILURE);
		}
		ft_game_init(&game, fd, argv[1]);
	}
	return 0;
}
