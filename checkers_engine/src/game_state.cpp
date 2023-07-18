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

#include "game_state.h"
#include "game.h"

GameState::GameState(Game& g)
    : game(g), board(g.board),
      move_count(g.move_count),
      move_count_since_last_capture(g.move_count_since_last_capture) {
}

GameState& GameState::operator=(const GameState& g) {
  board = g.board;
  move_count = g.move_count;
  move_count_since_last_capture = g.move_count_since_last_capture;
  return *this;
}

void GameState::restore() {
  game.board = board;
  game.move_count = move_count;
  game.move_count_since_last_capture = move_count_since_last_capture;
}
