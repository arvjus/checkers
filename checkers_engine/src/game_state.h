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

#include <array>
#include "board.h"

class Game;
class GameState {
public:
  GameState(Game& g);
  GameState& operator =(const GameState& g);
  void restore();

private:
  Game& game;
  Board board;
  std::uint16_t move_count;
  std::uint16_t move_count_since_last_capture;
};

template<typename T, int max_limit>
class vector_with_max_limit : public std::vector<T> {
public:
  void push_back_limited(const T& item) {
    if (std::vector<T>::size() >= max_limit)
      std::vector<T>::erase(std::vector<T>::begin());
    std::vector<T>::push_back(item);
  }
};
using game_state_vector = vector_with_max_limit<GameState, UNDO_MOVE_LIMIT>;

