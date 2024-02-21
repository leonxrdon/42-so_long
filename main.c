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

#include "so_long.h"

void load_map(Map *map) {
    //cargar el mapa con el arreglo que recibe como parametro, cargar el mapa en el arreglo
	map->map = malloc(sizeof(char *) * map->rows);
	if (!map->map)
	{
		printf("Error al cargar el mapa\n");
		exit(1);
	}
	int i = 0;
	while (i < map->rows)
	{
		map->map[i] = malloc(sizeof(char) * map->cols);
		if (!map->map[i])
		{
			printf("Error al cargar el mapa\n");
			exit(1);
		}
		i++;
	}
}

void mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color)
{
	int i = 0;
	while (i < height) {
		int j = 0;
		while (j < width) {
			mlx_pixel_put(mlx, win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_map(void *mlx, void *win, Map *map, Texture *wall_texture, Texture *user_texture, Texture *coin, Texture *salida)
{
	int block_size = 50;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			int x = j * block_size;
			int y = i * block_size;

			if (map->map[i][j] == '1') {
				mlx_put_image_to_window(mlx, win, wall_texture->img, x, y);
			} else if (map->map[i][j] == 'P') {
				mlx_put_image_to_window(mlx, win, user_texture->img, x, y);
			} else if (map->map[i][j] == 'C') {
				mlx_put_image_to_window(mlx, win, coin->img, x, y);
			} else if (map->map[i][j] == 'E') {
				mlx_put_image_to_window(mlx, win, salida->img, x, y);
			} else {
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x000000);
			}
		}
	}
}

Texture load_texture(void *mlx, char *file_path){
	Texture texture;
	texture.img = mlx_xpm_file_to_image(mlx, file_path, &texture.width, &texture.height);

	if (!texture.img) {
        printf("Error al cargar la textura desde %s\n", file_path);

	}
	return texture;
}

//dibujar la matriz en el mapa
void draw_map_matriz(void *mlx, void *win, char **map)
{
	int block_size;
	int	i;
	int	j;
	int	x;
	int	y;
	printf("entro a la funcion\n");
	printf("%c\n", map[0][0]);
	block_size = 50;
	i = 0;
	j = 0;
	while (i < 7)
	{
		while(j < 7)
		{
			x = j * block_size;
			y = i * block_size;
			j++;
			if (map[i][j] == '1')
				//color rojo
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFF0000);
			else if (map[i][j] == 'P')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x0000FF);
			else if (map[i][j] == 'C')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFF0000);
			else if (map[i][j] == 'E')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFFFF00);
			else
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x000000);
		}
		i++;
	}
}


int main(int argc, char **argv) {
	int		fd;
	void	*mlx;
	void	*mlx_win;
	char	**matriz;
	char	*gnl;
	// Map *str;
	t_vars	vars;
	// Texture	wall_texture;
	// Texture	user_texture;
	// Texture	coin_texture;
	// Texture	exit_texture;

	if (argc < 2)
		return (0);
	if (argv[0] != 0)
	{
		matriz = NULL;
		mlx = mlx_init();
		// Leer el mapa
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error al abrir el archivo\n");
			exit(1);
		}
		mlx_win = mlx_new_window(mlx, 7 * 50, 7 * 50, "so long");
		gnl = get_next_line(fd);
		while (gnl != NULL && gnl[0] != '\0')
		{
			printf("%s",gnl);
			matriz = ft_split(gnl, '\n');
			gnl = get_next_line(fd);
		}
		//imprimir la matriz
		printf("imprimiendo la matriz\n");
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				printf("%c", matriz[i][j]);
			}
			printf("\n");
		}
		draw_map_matriz(mlx, mlx_win, matriz);
		// // crear una funcion para cargar el mapa
		// // load_map(&str);
		// wall_texture = load_texture(mlx, "texturas/bloque.xpm");
		// user_texture = load_texture(mlx, "texturas/mario.xpm");
		// coin_texture = load_texture(mlx, "texturas/coin.xpm");
		// exit_texture = load_texture(mlx, "texturas/salida.xpm");

		// draw_map(mlx, mlx_win, &str, &wall_texture, &user_texture, &coin_texture, &exit_texture);
		mlx_hook(mlx_win, 2, 1L<<0, move, &vars);
		mlx_key_hook(mlx_win, move, &vars);
		mlx_loop(mlx);
	}
	return 0;
}
