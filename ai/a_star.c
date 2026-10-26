#include "search.h"
#include "../src/queue.h"
#include "../src/stack.h"
#include "../src/heap.h"
#include <math.h>
#include <string.h>

extern int map_width;
extern int map_height;
extern Stack ai_path;
extern Queue search_path;

//typedef struct {
//    vec2 pos;
//    vec2 parent_pos;
//    double f;
//    double g;
//    double h;
//} Node;

// 启发式函数
double heuristic(vec2 curr_pos, vec2 end_pos)
{
    // 四方向用曼哈顿距离
    return abs(curr_pos.x - end_pos.x) + abs(curr_pos.y - end_pos.y);
    // 欧几里得距离
    //    return sqrt((curr_pos.x - end_pos.x) * (curr_pos.x - end_pos.x) + 
    //(curr_pos.y - end_pos.y) * (curr_pos.y - end_pos.y));
}



bool a_star(const char *map, vec2 start, vec2 end)
{
    // 初始化开放列表和关闭列表
    Heap open_list = h_create();

    // @ai 原来使用指针数组，出现悬空指针，ai建议使用结构体映射（map）
    typedef struct {
        bool visited;
        vec2 parent;
    } ClosedCell;
    ClosedCell closed_list[map_height][map_width];
    memset(closed_list, 0, sizeof(closed_list));

    // 记录每个格子的最优g
    double g_score[map_height][map_width];
    for (int y = 0; y < map_height; y++)
        for (int x = 0; x < map_width; x++)
            g_score[y][x] = 1000;

    Node start_node;
    start_node.pos = start;
    start_node.parent = start;
    start_node.g = 0.0;
    start_node.h = heuristic(start, end);
    start_node.f = start_node.g + start_node.h;

    g_score[start.y][start.x] = 0.0;
    h_add(&open_list, start_node);

    while (!h_empty(&open_list)) {
        Node curr_node = h_delete(&open_list);
        q_add(&search_path, curr_node.pos);

        // 检测是否已经拜访过了
        if (closed_list[curr_node.pos.y][curr_node.pos.x].visited)
            continue;
        closed_list[curr_node.pos.y][curr_node.pos.x].visited = true;
        closed_list[curr_node.pos.y][curr_node.pos.x].parent = curr_node.parent;
        
        // 回溯
        if (vec2_equals(curr_node.pos, end)) {
            vec2 parent_pos = curr_node.pos;
            while (!vec2_equals(parent_pos, start)) {
                s_add(&ai_path, parent_pos);
                parent_pos = closed_list[parent_pos.y][parent_pos.x].parent;
            }
            return true;
        }

        // 移动
        const vec2 dir[4] = {
            { 1, 0 },   // 右
            { -1, 0 },  // 左
            { 0, -1 },  // 上
            { 0, 1 }    // 下
        };
        for (int i = 0; i < 4; i++) {
            vec2 next_pos = {
                curr_node.pos.x + dir[i].x,
                curr_node.pos.y + dir[i].y
            };

            // 边界检查
            if (next_pos.x < 0 || next_pos.x >= map_width ||
                next_pos.y < 0 || next_pos.y >= map_height)
                continue;

            // 墙壁检查
            if (map[next_pos.y * map_width + next_pos.x] == '#')
                continue;

            // 检查是否已位于关闭列表
            if (closed_list[next_pos.y][next_pos.x].visited)
                continue;

            // 添加邻居
            double next_g = curr_node.g + 1;
            
            if (next_g < g_score[next_pos.y][next_pos.x]) {
                g_score[next_pos.y][next_pos.x] = next_g;
                
                Node next_node;
                next_node.pos = next_pos;
                next_node.parent = curr_node.pos;
                next_node.g = curr_node.g + 1;
                next_node.h = heuristic(next_pos, end);
                next_node.f = next_node.g + next_node.h;
                h_add(&open_list, next_node);
                

            }
        }
    }
    
    return false;
}
