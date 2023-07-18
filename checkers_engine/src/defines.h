#pragma once

#include <cinttypes>

#define ASSERT_POS(pos)  assert((pos) >= 1 && (pos) <= 32)

static const unsigned short BOARD_WIDTH = 4;
static const unsigned short BOARD_HEIGHT = 8;
static const unsigned short BOARD_SIZE = BOARD_WIDTH * BOARD_HEIGHT;
static const unsigned short INITIAL_NUMBER_OF_PIECES_PER_PLAYER = 12;
static const unsigned short CONSECUTIVE_NON_CAPTURE_MOVE_LIMIT = 40;
static const unsigned short UNDO_MOVE_LIMIT = 5;

using Row = std::uint8_t;
using Col = std::uint8_t;
using score = long;

enum class Player : std::uint8_t {
  Undef = 0,
  Black = 1,
  White = 2
};

