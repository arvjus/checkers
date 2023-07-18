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

#include <vector>
#include "defines.h"

class Pos {
public:
  Pos(std::uint8_t p);
  operator std::uint8_t() const;
  std::uint8_t operator ++(int);
  [[nodiscard]] std::uint16_t get_index() const;
  [[nodiscard]] Row get_row() const;
  [[nodiscard]] Col get_col() const;
  [[nodiscard]] Col get_col8() const;
  [[nodiscard]] bool on_edge() const;
  [[nodiscard]] std::uint8_t get_distance_to(Pos other) const;

  static bool is_valid(std::uint8_t pos);
  static Pos none;

private:
  std::uint8_t pos;
  static std::vector<uint8_t> edges;
};
