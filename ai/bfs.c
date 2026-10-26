#include "search.h"
#include "../src/queue.h"
#include "../src/stack.h"

extern int map_width;
extern int map_height;
extern Stack ai_path;
extern Queue search_path;

bool bfs(const char *map, vec2 start, vec2 end)
{
    // 初始化已处理和回溯表
    bool visited[map_height][map_width];
    for (int y = 0; y < map_height; y++)
        for (int x = 0; x < map_width; x++)
            visited[y][x] = false;
    vec2 parent[map_height][map_width];
    for (int y = 0; y < map_height; y++)
        for (int x = 0; x < map_width; x++)
            parent[y][x] = (vec2){ -1, -1 };

    // 初始化子路径队列
    Queue queue = q_create();
    q_add(&queue, start);
    visited[start.y][start.x] = true;

    // 开始寻路
    while (!q_empty(&queue)) {
        vec2 curr_pos = q_delete(&queue);

        // 加入探索路径
        q_add(&search_path, curr_pos);
        
        // 如果到达终点 回溯
        if (vec2_equals(curr_pos, end)) {
            vec2 p_pos = { curr_pos.x, curr_pos.y };
            while (parent[p_pos.y][p_pos.x].x != -1 && parent[p_pos.y][p_pos.x].y != -1) {
                vec2 t_pos = parent[p_pos.y][p_pos.x];
                s_add(&ai_path, p_pos);
                p_pos = t_pos;
            }
            return true;
        }

        // 分别向四个方向移动 @ai
        const vec2 dir[] = {
            {  1,  0 },
            { -1,  0 },
            {  0,  1 },
            {  0, -1 }
        };
        
        for (int i = 0; i < 4; i++) {
            vec2 n_pos = {
                curr_pos.x + dir[i].x,
                curr_pos.y + dir[i].y
            };
            
            // 检测数组越界
            if (n_pos.x < 0 || n_pos.x >= map_width || n_pos.y < 0 || n_pos.y >= map_height)
                continue;
            // 检测已拜访
            if (visited[n_pos.y][n_pos.x])
                continue;
            // 检测墙壁
            if (map[n_pos.y * map_width + n_pos.x] == '#')
                continue;

            // 如果可以移动
            visited[n_pos.y][n_pos.x] = true;
            parent[n_pos.y][n_pos.x] = curr_pos;
            q_add(&queue, n_pos);
        }
    }
    
    return false;
}


