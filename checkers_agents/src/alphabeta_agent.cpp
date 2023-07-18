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

#include <iostream>
#include <ctime>
#include <climits>
#include "checkers_config.h"
#include "early_heuristic.h"
#include "late_heuristic.h"
#include "utils.h"
#include "alphabeta_agent.h"

AlphabetaAgent::AlphabetaAgent(int m_duration, int m_depth, Player p)
  : HeuristicAgent(m_duration, "alphabeta", p), max_depth(m_depth) {
}

AlphabetaAgent::~AlphabetaAgent() = default;

scored_move AlphabetaAgent::score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const {
  assert(board.whose_turn() == maximizing_player);

  Board new_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
  auto depth = game_phase == GamePhase::END_GAME ? max_depth : max_depth - 1;
  uint32_t count = 0;
  auto score = alphabeta(game_phase, new_board, depth, false, LONG_MIN, LONG_MAX, timeout, count);

#ifdef VERBOSE_EVEN_MORE
  std::cout << name + " - move: " << (int)move.src << "," << (int)move.dst << ", score: " << score << ", count: " << count << std::endl;
#endif
  return scored_move{score, move};
}

score AlphabetaAgent::alphabeta(GamePhase game_phase, const Board& board, int depth, bool maximizing, score alpha, score beta, uint32_t timeout, uint32_t& count) const {
  count++;

  auto possible_moves = board.get_possible_moves();
  if (depth == 0 || possible_moves.empty())
    return game_phase == GamePhase::END_GAME ?
                 LateHeuristicValue::get_score(maximizing_player, board) :
                 EarlyHeuristicValue::get_score(maximizing_player, board);

  if (maximizing) {
    score value = LONG_MIN;
    for (auto move : possible_moves) {
      auto child_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
      value = std::max(value, alphabeta(game_phase, child_board, depth - 1, false, alpha, beta, timeout, count));
      if (time(nullptr) > timeout || value > beta)
        break;
      alpha = std::max(alpha, value);
    }
    return value;
  } else {
    score value = LONG_MAX;
    for (auto move : possible_moves) {
      auto child_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
      value = std::min(value, alphabeta(game_phase, child_board, depth - 1, true, alpha, beta, timeout, count));
      if (time(nullptr) > timeout || value < alpha)
        break;
      beta = std::min(beta, value);
    }
    return value;
  }
}
