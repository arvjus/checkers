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

#include <algorithm>
#include "move.h"
#include "piece.h"

class Utils {
public:
  Utils();
  static int take_random(size_t max);

private:
  static Utils instance;
};

template <typename T>
inline const T& take_random(const std::vector<T>& vector) {
  return vector.at(Utils::take_random(vector.size()));
};

template <typename T>
inline bool vector_contains(const std::vector<T>& vector, const T& element) {
  return std::find(vector.begin(), vector.end(), element) != vector.end();
};

score interpolate(score in_value, score in_min, score in_max, short out_min, short out_max);
std::string move_to_string(const Move& move);
std::string piece_to_string(const Piece& piece);

