#include "search.h"
#include <string.h>
#include "../src/queue.h"
#include "../src/stack.h"

extern int map_width;
extern int map_height;
extern Stack ai_path;
extern Queue ai_path_queue;

/* bool dfs(char *map, vec2 pos, vec2 end) */
/* { */
/*     if (pos.x >= map_width || pos.y >= map_height) */
/*         return false; */
/*     char c = map[pos.y * map_width + pos.x]; */
    
/*     // 障碍, 走过, 死路 */
/*     if (c == '#' || c == '*' || c == 'x') */
/*         return false; */

/*     // 到达终点 */
/*     if (c == 'B') { */
/*         return true; */
/*     } */

/*     // 标记路径 */
/*     if (c != 'A') { */
/*         map[pos.y * map_width + pos.x] = '*'; */
/*         q_add(&ai_path_queue, pos); */
/*     } */

/*     // 分别向四个方向移动 */
/*     const vec2 dir[] = { */
/*         {  1,  0 }, */
/*         { -1,  0 }, */
/*         {  0,  1 }, */
/*         {  0, -1 } */
/*     }; */
/*     for (int i = 0; i < 4; i++) { */
/*         vec2 next_pos = { */
/*             pos.x + dir[i].x, */
/*             pos.y + dir[i].y */
/*         }; */
/*         if (next_pos.x < 0 || next_pos.y < 0) */
/*             continue; */
/*         if (dfs(map, next_pos, end)) */
/*             return true; */
/*     } */

/*     if (c != 'A') { */
/*         map[pos.y * map_width + pos.x] = 'x'; */
/*     } */
    
/*     return false; */
/* } */

// 基于栈 @ai

bool dfs(const char *map, vec2 start, vec2 end)
{
    bool visited[map_height][map_width];
    memset(visited, 0, sizeof(visited));
    Stack stack = s_create();
    s_add(&stack, start);
    visited[start.y][start.x] = true;

    
    while(!s_empty(&stack)) {
        vec2 curr_pos = s_delete(&stack);

          // 记录"实际访问到"的格子
        q_add(&ai_path_queue, curr_pos);
        
        if (vec2_equals(curr_pos, end))
            return true;

        const vec2 dir[] = {
            {  0,  -1 },
            {  0, 1 },
            {  -1,  0 },
            { 1,  0 },
        };
        for (int i = 0; i < 4; i++) {
            vec2 next = {
                curr_pos.x + dir[i].x,
                curr_pos.y + dir[i].y
            };

            // 先做边界检查
            if (next.x < 0 || next.x >= map_width ||
                next.y < 0 || next.y >= map_height)
                continue;

            if (visited[next.y][next.x])
                continue;
            if (map[next.y * map_width + next.x] == '#')
                continue;
            
            visited[next.y][next.x] = true;
            s_add(&stack, next);
            /* s_add(&ai_path, next); */
        }
    }
    
    return false;
}
