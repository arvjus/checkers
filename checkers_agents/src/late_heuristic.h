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

#include "basic_heuristic.h"

class LateHeuristicValue : public BasicHeuristicValue{
public:
  [[nodiscard]] static score get_score(Player player, const Board& board);
  bool static has_the_move(Player player, const Board& board);

protected:
  [[nodiscard]] static score score_single_corner_distances(const std::vector<Piece>& inventory);
  [[nodiscard]] static score score_double_corner_distances(const std::vector<Piece>& inventory);
  [[nodiscard]] static score score_opponent_distances(const std::vector<Piece>& players_inventory, const std::vector<Piece>& opponents_inventory);
};