#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAP_HEIGHT 6
#define MAP_WIDTH 10

typedef struct {
    int x;
    int y;
    int toplanan_toplar;
} t_player;

typedef struct {
    char **map;
    t_player player;
} t_game;

void init_game(t_game *game) {
    game->map = malloc(MAP_HEIGHT * sizeof(char *));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        game->map[i] = malloc(MAP_WIDTH + 1); // +1 for null terminator
    }

    // Haritayı başlat (örnek harita)
    char *initial_map[MAP_HEIGHT] = {
        "1111111111",
        "1000T0001",
        "101111101",
        "10T000T01",
        "1111P1111",
        "1111111111"
    };

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game->map[i][j] = initial_map[i][j];
            if (initial_map[i][j] == 'P') {
                game->player.x = j;
                game->player.y = i;
            }
        }
    }

    game->player.toplanan_toplar = 0; // Toplanan topları başlat
}

void render_map(t_game *game) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        printf("%s\n", game->map[i]);
    }
}

void move_player(t_game *game, char move) {
    int new_x = game->player.x;
    int new_y = game->player.y;

    if (move == 'w') new_y--;
    else if (move == 's') new_y++;
    else if (move == 'a') new_x--;
    else if (move == 'd') new_x++;

    // Harita sınırları içinde kal
    if (new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT) {
        return;
    }

    // Yeni konum geçerli mi kontrol et
    if (game->map[new_y][new_x] == '1') {
        return;
    }

    // Topu al
    if (game->map[new_y][new_x] == 'T') {
        game->map[new_y][new_x] = '0'; // Topu haritadan kaldır
        game->player.toplanan_toplar++; // Toplanan topları artır
    }

    // Messi'nin konumunu güncelle
    game->map[game->player.y][game->player.x] = '0'; // Eski konumu boşalt
    game->player.x = new_x;
    game->player.y = new_y;
    game->map[game->player.y][game->player.x] = 'P'; // Yeni konuma Messi'yi yerleştir
}

int main(void) {
    t_game game;
    char move;
    int toplam_top_sayisi = 3; // Haritadaki toplam top sayısı

    init_game(&game);

    while (game.player.toplanan_toplar < toplam_top_sayisi) {
        render_map(&game);
        scanf(" %c", &move); // Kullanıcıdan hareket al
        move_player(&game, move);
        usleep(100000); // 0.1 saniye bekle (hareketi daha görünür hale getirmek için)
        // system("clear"); // Terminali temizle (kaldırıldı veya gerektiğinde kullanılacak)
    }

    printf("Tebrikler! Tüm topları topladınız!\n");

    // Oyun sonunda haritayı serbest bırak
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(game.map[i]);
    }
    free(game.map);

    return (0);
}