CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c \
src/*.c \
ai/bfs.c ai/dfs.c ai/a_star.c

INCLUDE_FLAGS	= -Ithird/SDL3/include -Ithird/SDL3_ttf/include
LIB_FLAGS	= -Lthird/SDL3/lib -Lthird/SDL3_ttf/lib
LD_FLAGS	= -lSDL3 -lSDL3_ttf

all:
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDE_FLAGS) $(LIB_FLAGS) $(LD_FLAGS) -o search

run:
	./search
