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

#include <cmath>
#include "pos.h"
#include "utils.h"

Pos Pos::none = 0;

std::vector<uint8_t> Pos::edges = {4, 5, 12, 13, 20, 21, 28, 29};

Pos::Pos(std::uint8_t p) : pos(p) {
}

std::uint8_t Pos::operator++(int) {
  return pos ++;
}

Pos::operator std::uint8_t() const {
  return pos;
}

std::uint16_t Pos::get_index() const {
  return pos - 1;
}

Row Pos::get_row() const {
  return static_cast<Row>((pos - 1) / BOARD_WIDTH + 1);
}

Col Pos::get_col() const { return (pos - 1) % BOARD_WIDTH + 1; }

Col Pos::get_col8() const {
  return (pos - 1) % BOARD_WIDTH * 2 + get_row() % 2 + 1;
}

std::uint8_t Pos::get_distance_to(Pos other) const {
  auto dist = std::max(abs(get_row() - other.get_row()), abs(get_col8() - other.get_col8()));
  return static_cast<std::uint8_t>(dist);
}

bool Pos::on_edge() const {
  return vector_contains(edges, pos);
}

bool Pos::is_valid(std::uint8_t pos) {
  return pos >= 1 && pos <= 32;
}
