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

#include "agent.h"
#include "game.h"

class HeuristicAgent : public Agent {
public:
  HeuristicAgent(int md, std::string n = "heuristic", Player p = Player::Black);
  ~HeuristicAgent() override;
  [[nodiscard]] virtual scored_move score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const;

protected:
  const int max_duration;
  std::vector<scored_move> scored_moves;

  [[nodiscard]] best_move_with_scores search_next_move(const std::unique_ptr<Game>& game) const override;
};