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

#include <memory>
#include "game.h"

using scored_move = std::pair<score, Move>;
using vector_of_scored_moves = std::vector<scored_move>;
using best_move_with_scores = std::pair<Move, vector_of_scored_moves>;

class Agent {
public:
  Agent(std::string n, Player p = Player::Black);
  [[nodiscard]] virtual best_move_with_scores next_move(const std::unique_ptr<Game>& game) const final;
  virtual ~Agent();

protected:
  const std::string name;
  const Player maximizing_player;

  [[nodiscard]] virtual best_move_with_scores search_next_move(const std::unique_ptr<Game>& game) const;
  static Player swap(Player player);
};