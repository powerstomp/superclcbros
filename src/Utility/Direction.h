#ifndef _DIRECTION_H
#define _DIRECTION_H

enum class Direction {
	NONE,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	MAX
};

static inline Direction GetOppositeDirection(Direction direction) {
	switch (direction) {
	case Direction::LEFT:
		return Direction::RIGHT;
	case Direction::RIGHT:
		return Direction::LEFT;
	case Direction::UP:
		return Direction::DOWN;
	case Direction::DOWN:
		return Direction::UP;
	default:
		return Direction::NONE;
	}
}

#endif
