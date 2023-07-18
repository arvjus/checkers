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

#include <chrono>
#include "utils.h"
#include "move.h"
#include "piece.h"

Utils Utils::instance;

Utils::Utils() {
  std::srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int Utils::take_random(size_t max) {
  return std::rand() % max;
}

std::string move_to_string(const Move& move) {
  char buf[10];
  snprintf(buf, sizeof(buf), "%d->%d",
           static_cast<int>(move.src),
           static_cast<int>(move.dst));
  return {buf};
}

std::string piece_to_string(const Piece& piece) {
  char buf[10];
  char player = piece.get_player() == Player::Black ? 'b' : 'w';
  snprintf(buf, sizeof(buf), "%c%d",
           piece.is_king() ? toupper(player) : player,
           static_cast<int>(piece.get_pos()));
  return {buf};
}

score interpolate(score in_value, score in_min, score in_max, short out_min, short out_max) {
  if (in_min == in_max)
    return out_min;

  double f = double(in_value - in_min) / double(in_max - in_min);
  return static_cast<score>(out_min + (out_max - out_min) * f);
}
