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

#include "pos.h"
#include <cassert>

struct Move {
  Move(Pos s, Pos d);
  bool operator==(const Move& rhs) const;
  bool is_capture_move() const;

  static Move none;
  Pos src;
  Pos dst;
};

inline Move::Move(Pos s, Pos d) : src(s), dst(d) {
  ASSERT_POS(src);
  ASSERT_POS(dst);
  assert(src != dst);
}

inline bool Move::operator==(const Move& rhs) const {
  return src == rhs.src && dst == rhs.dst;
}

inline bool Move::is_capture_move() const {
  auto dist = std::abs(src - dst);
  return dist == 7 || dist == 9;
}

inline Move Move::none {1, 32};


