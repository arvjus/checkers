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

#include <numeric>
#include <iostream>
#include <climits>
#include "late_heuristic.h"
#include "scores.h"

std::vector<Pos> double_corner_positions = {1, 5, 28, 32};

score LateHeuristicValue::get_score(Player player, const Board& board) {
  auto score = BasicHeuristicValue::get_score(player, board);

  auto players_inventory = board.get_available_inventory(player);
  auto opponents_inventory = board.get_available_inventory(get_opponent(player));

  bool the_move = has_the_move(player, board);
  if (the_move || players_inventory.size() > opponents_inventory.size())
    score += score_opponent_distances(players_inventory, opponents_inventory);
  else
    score += score_double_corner_distances(players_inventory);

  score += score_single_corner_distances(opponents_inventory);

  return score;
}

score LateHeuristicValue::score_single_corner_distances(const std::vector<Piece>& inventory) {
  return std::transform_reduce(inventory.begin(), inventory.end(), 0, std::plus<>(),
                               [](auto piece) {
    auto distance = std::min(piece.get_pos().get_distance_to(4), piece.get_pos().get_distance_to(29));
    return distance * -SCORE_SINGLE_CORNER_DISTANCES; // closer is better
  });
}

score LateHeuristicValue::score_double_corner_distances(const std::vector<Piece> &inventory) {
  return std::transform_reduce(
      inventory.begin(), inventory.end(), 0, std::plus<>(), [](auto piece) {
        auto min_dist = CHAR_MAX;
        for (auto pos : double_corner_positions) {
          auto dist = piece.get_pos().get_distance_to(pos);
          if (dist < min_dist)
            min_dist = dist;
        }
        return (min_dist == CHAR_MAX ? 0 : min_dist) * -SCORE_DOUBLE_CORNER_DISTANCES; // closer is better
      });
}

score LateHeuristicValue ::score_opponent_distances(const std::vector<Piece>& players_inventory, const std::vector<Piece>& opponents_inventory) {
  return std::transform_reduce(
      players_inventory.begin(), players_inventory.end(), 0, std::plus<>(), [opponents_inventory](auto piece) {
        auto min_dist = CHAR_MAX;
        for (auto opponent_piece : opponents_inventory) {
          auto dist = piece.get_pos().get_distance_to(opponent_piece.get_pos());
          if (dist < min_dist)
            min_dist = dist;
        }
        return (min_dist == CHAR_MAX ? 0 : min_dist) * -SCORE_OPPONENT_DISTANCES; // closer is better
      });
}

bool LateHeuristicValue::has_the_move(Player player, const Board& board) {
  auto whose_turn = board.whose_turn();
  auto inventory1 = board.get_available_inventory(whose_turn);
  auto inventory2 = board.get_available_inventory(get_opponent(whose_turn));
  if (inventory1.size() != inventory2.size())
    return false;

  // count pieces on add rows black's turn, otherwise count pieces on event rows
  auto counter = [whose_turn](auto piece) {
    auto mod = piece.get_pos().get_row() % 2;
    return (whose_turn == Player::Black && mod || whose_turn == Player::White && mod == 0) ? 1 : 0;
  };

  auto count = std::transform_reduce(inventory1.begin(), inventory1.end(), 0, std::plus<>(), counter) +
               std::transform_reduce(inventory2.begin(), inventory2.end(), 0, std::plus<>(), counter);
  return (count % 2 && player == whose_turn) || (count % 2 == 0 && player != whose_turn);
}
