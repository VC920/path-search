#ifndef SEARCH_H
#define SEARCH_H

#include "../src/vec2.h"

bool dfs(const char *map, vec2 start, vec2 end);
bool bfs(const char *map, vec2 start, vec2 end);
bool a_star(const char *map, vec2 start, vec2 end);

#endif//SEARCH_H
