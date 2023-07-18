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

#include "basic_heuristic.h"
#include "scores.h"

score BasicHeuristicValue::get_score(Player player, const Board& board) {
  Player opponent = get_opponent(player);
  auto score = 0l;

  // inventory
  auto counts = board.count_available_inventory(player);
  score += get<0>(counts) * SCORE_PIECE + get<1>(counts) * SCORE_KING;
  score -= get<2>(counts) * SCORE_PIECE + get<3>(counts) * SCORE_KING;

  // captures
  score -= static_cast<long>(board.get_possible_capture_moves(opponent).size() * SCORE_POSSIBLE_CAPTURE);
  return score;
}

Player BasicHeuristicValue::get_opponent(const Player &player) {
  return player == Player::Black ? Player::White : Player::Black;
}
