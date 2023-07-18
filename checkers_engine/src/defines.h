/* Copyright (c) 2022, Arvid Juskaitis (arvydas.juskaitis@gmail.com)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1335  USA */

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

