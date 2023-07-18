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

#include <utility>
#include "agent.h"

Agent::Agent(std::string n, Player p)
  : name(std::move(n)), maximizing_player(p) {
}

Agent::~Agent() = default;

best_move_with_scores Agent::next_move(const std::unique_ptr<Game>& game) const {
  auto possible_moves = game->get_board().get_possible_moves();
  if (possible_moves.empty())
    return best_move_with_scores{Move::none, vector_of_scored_moves()};
  if (possible_moves.size() == 1)
    return best_move_with_scores{possible_moves.at(0), vector_of_scored_moves()};
  else
    return search_next_move(game);
}

best_move_with_scores Agent::search_next_move(const std::unique_ptr<Game>& game) const {
  return best_move_with_scores{Move::none, vector_of_scored_moves()};
}

Player Agent::swap(Player player) {
  return player == Player::Black ? Player::White : Player::Black;
}
