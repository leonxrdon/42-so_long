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
#include <mlx.h>
#include <stdio.h>

#define MAP_WIDTH 7
#define MAP_HEIGHT 7

typedef struct {
    char map[MAP_HEIGHT][MAP_WIDTH];
} Map;

typedef struct {
    void *img;
    int width;
    int height;
} Texture;

void load_map(Map *map) {
    // Definir manualmente el mapa o leerlo desde un archivo de texto
    char temp_map[MAP_HEIGHT][MAP_WIDTH] = {
        "1111111",
        "1P0010E",
        "1C00101",
        "1000101",
        "10C0101",
        "1000001",
        "1111111"
    };

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map->map[i][j] = temp_map[i][j];
        }
    }
}

void mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color) {
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

void draw_map(void *mlx, void *win, Map *map, Texture *texture) {
    int block_size = 30; // Tamaño de cada bloque en píxeles
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int x = j * block_size;
            int y = i * block_size;

            if (map->map[i][j] == '1') {
                // Dibujar pared con textura
                mlx_put_image_to_window(mlx, win, texture->img, x, y);
            } else if (map->map[i][j] == 'P') {
                // Dibujar posición inicial con textura
                mlx_put_image_to_window(mlx, win, texture->img, x, y);
            } else if (map->map[i][j] == 'C') {
                // Dibujar coleccionable con textura
                mlx_put_image_to_window(mlx, win, texture->img, x, y);
            } else if (map->map[i][j] == 'E') {
                // Dibujar salida con textura
                mlx_put_image_to_window(mlx, win, texture->img, x, y);
            }
            // No dibujar nada para espacios vacíos ('0')
        }
    }
}

Texture load_texture(void *mlx, char *file_path) {
    Texture texture;

    // Cargar la textura desde el archivo .xpm
    texture.img = mlx_xpm_file_to_image(mlx, file_path, &texture.width, &texture.height);

    if (!texture.img) {
        printf("Error al cargar la textura desde %s\n", file_path);
    }
    return texture;
}



int main(void) {
    void *mlx;
    void *mlx_win;
    Map game_map;
	Texture	wall_texture;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, MAP_WIDTH * 30, MAP_HEIGHT * 30, "so long");

    load_map(&game_map);
    wall_texture = load_texture(mlx, "block.xpm");

    draw_map(mlx, mlx_win, &game_map, &wall_texture);


    mlx_loop(mlx);

    return 0;
}
