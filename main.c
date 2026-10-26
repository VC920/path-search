#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "src/renderer.h"
#include "src/stack.h"
#include "src/queue.h"
#include "src/vec2.h"
#include "ai/search.h"

/* map */
//#include "maze1.h"
#include "maze2.h"
//#include "maze3.h"

#define CELL_SIZE 50

typedef struct {
    vec2 pos;
    int size;
} Player;

Stack ai_path;
Queue ai_path_queue;

Queue search_path;

int map_width = MAP_WIDTH;
int map_height = MAP_HEIGHT;

typedef enum {
    DFS,
    BFS,
    A_STAR,
} Mode;
Mode mode = BFS;
char *mode_name = "BFS";
bool is_pause = false;
float time = 150;

int main(void)
{
    // SDL init
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("sean game", MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE, 0);

    // Renderer init
    renderer_init(window);

 start:
    // Clear map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y * MAP_WIDTH + x] == '*')
                map[y * MAP_WIDTH + x] = ' ';
            if (map[y * MAP_WIDTH + x] == '.')
                map[y * MAP_WIDTH + x] = ' ';
        }
    }
    
    // Get begin and end pos
    vec2 begin;
    vec2 end;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y * MAP_WIDTH + x] == 'A') 
                begin = (vec2){ x, y };
            if (map[y * MAP_WIDTH + x] == 'B')
                end = (vec2){ x, y };
        }
    }

    // Player
    Player player = { begin, CELL_SIZE / 2 };
    
    ai_path = s_create();
    ai_path_queue = q_create();
    search_path = q_create();

    bool search_done = false;
    
    /* Search */
    if (mode == DFS)
        dfs(map, begin, end);
    else if (mode == BFS)
        bfs(map, begin, end);
    else if (mode == A_STAR)
        a_star(map, begin, end);

    // Loop
    bool running = true;
    while (running) {
        // Process event
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == 'r')
                    // forgive me dijkstra in your algorithm i use goto
                    goto start;
                else if (event.key.key == 'd') {
                    mode = DFS;
                    mode_name = "DFS";
                    goto start;
                }
                else if (event.key.key == 'b') {
                    mode = BFS;
                    mode_name = "BFS";
                    goto start;
                }
                else if (event.key.key == 'a') {
                    mode = A_STAR;
                    mode_name = "A*";
                    goto start;
                }
                else if (event.key.key == ' ') {
                    is_pause = !is_pause;
                }
            }
        }

        // player move

        if (!is_pause) {

            if (!q_empty(&search_path)) {
                vec2 search_pos = q_delete(&search_path);
                if (map[search_pos.y * map_width + search_pos.x] == ' ')
                    map[search_pos.y * map_width + search_pos.x] = '.';
            } else {
                search_done = true;
            }
        
            if (search_done) {
                if (!s_empty(&ai_path))
                    player.pos = s_delete(&ai_path);
                else if (!q_empty(&ai_path_queue))
                    player.pos = q_delete(&ai_path_queue);
                else
                    goto start;
            }
        
            // show path
            if (map[player.pos.y * MAP_WIDTH + player.pos.x] == ' ' ||
                map[player.pos.y * MAP_WIDTH + player.pos.x] == '.')
                map[player.pos.y * MAP_WIDTH + player.pos.x] = '*';
        }
        
        // Render
        renderer_clear(0, 0, 0, 255);

        // Draw map
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                char c = map[y * MAP_WIDTH + x];
                switch (c) {
                case '#':
                    renderer_draw_rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE -1, CELL_SIZE -1, 128, 128, 128, 255);                    
                    break;
                case 'A':
                    renderer_draw_rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE -1, CELL_SIZE -1, 0, 255, 0, 255);
                    break;
                case 'B':
                    renderer_draw_rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE -1, CELL_SIZE -1, 255, 0, 0, 255);
                    break;
                case '*':
                    renderer_draw_rect((x * CELL_SIZE) + (player.size / 2), (y * CELL_SIZE) + (player.size / 2), player.size, player.size, 00, 50, 00, 255);
                    break;
                case '.':
                    renderer_draw_rect(x * CELL_SIZE, y * CELL_SIZE , CELL_SIZE - 1 , CELL_SIZE - 1, 50, 50, 0, 255);
                    break;
                }
            }
        }

        // Draw player
        renderer_draw_rect((player.pos.x * CELL_SIZE) + (player.size / 2),
                           (player.pos.y * CELL_SIZE) + (player.size / 2),
                           player.size,
                           player.size,
                           255, 255, 255, 255);

        renderer_draw_text(0, 0, mode_name, strlen(mode_name));

        if (is_pause)
            renderer_draw_text(0, 100, "PAUSE", 5);
        
        renderer_present();

        // FPS fix
        SDL_Delay(time);
    }

    // Quit
    renderer_destroy();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

