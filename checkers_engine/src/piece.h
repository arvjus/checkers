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

#include <cmath>
#include <string>
#include "pos.h"

static const std::uint8_t BITMASK_PLAYER = 0b11000000;
static const std::uint8_t BITMASK_KING = 0b00100000;
static const std::uint8_t BITMASK_POS = 0b00011111;

class Piece {
public:
  Piece();
  Piece(Pos pos, Player p = Player::Undef, bool king = false);
  bool operator==(const Piece& piece) const;
  [[nodiscard]] Player get_player() const;
  [[nodiscard]] bool is_on_king_row() const;
  [[nodiscard]] bool is_king() const;
  [[nodiscard]] Pos get_pos() const;
  void move(Pos pos);

  static Piece create(std::string str);

private:
  std::uint8_t databits;
};

static_assert(sizeof(Piece) == 1, "invalid Piece size");
