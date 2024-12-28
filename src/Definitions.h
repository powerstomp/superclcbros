#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

constexpr inline int MICROSECONDS_PER_SECOND = 1000000;
constexpr inline int TICKS_PER_SECOND = 40;
constexpr inline int TIME_PER_TICK = MICROSECONDS_PER_SECOND / TICKS_PER_SECOND;

constexpr inline int WINDOW_WIDTH = 1000;
constexpr inline int WINDOW_HEIGHT = 600;

constexpr inline int TILE_SIZE = 50;
constexpr inline int WINDOW_WIDTH_IN_TILES = WINDOW_WIDTH / TILE_SIZE;
constexpr inline int WINDOW_HEIGHT_IN_TILES = WINDOW_HEIGHT / TILE_SIZE;

#endif
