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

#include <future>
#include <utility>
#include <iostream>
#include <ctime>
#include "checkers_config.h"
#include "early_heuristic.h"
#include "late_heuristic.h"
#include "heuristic_agent.h"
#include "utils.h"

#define SCORE_MOVE_MULTITHREADED true

HeuristicAgent::HeuristicAgent(int md, std::string n, Player p)
    : Agent(std::move(n), p), max_duration(md) {
}

HeuristicAgent::~HeuristicAgent() = default;

best_move_with_scores HeuristicAgent::search_next_move(const std::unique_ptr<Game>& game) const {
  auto possible_moves = game->get_board().get_possible_moves();
  assert(possible_moves.size() > 1);

  GamePhase game_phase = game->get_game_phase();
  const Board& board = game->get_board();
  uint32_t timeout = time(nullptr) + max_duration;
  vector_of_scored_moves scored_moves;
#if SCORE_MOVE_MULTITHREADED
  using scored_move_future = std::future<scored_move>;
  std::vector<scored_move_future> scored_move_futures;
  for (auto move : possible_moves) {
    std::future<scored_move> future = std::async(std::launch::async, &HeuristicAgent::score_move, this, game_phase, board, move, timeout);
    scored_move_futures.push_back(std::move(future));
  }
  std::transform(scored_move_futures.begin(), scored_move_futures.end(),
                 std::back_inserter(scored_moves),
                 [](scored_move_future& future) {return future.get(); });
#else
  std::transform(possible_moves.begin(), possible_moves.end(),
                 std::back_inserter(scored_moves),
                 [this, game_phase, board, timeout](const Move& move) {return this->score_move(game_phase, board, move, timeout);});
#endif
  auto scored_moves_comp = [](auto l, auto r) { return l.first < r.first; };
  std::sort(scored_moves.begin(), scored_moves.end(), scored_moves_comp);
  auto max_scored_move = std::max_element(scored_moves.begin(), scored_moves.end(), scored_moves_comp);
  auto max_scored_move_count = scored_moves.end() - max_scored_move;
  auto next_move = max_scored_move_count ? (max_scored_move + Utils::take_random(max_scored_move_count))->second : Move::none;

#ifdef VERBOSE
  std::cout << name + " - selected move: " << (int)next_move.src << "," << (int)next_move.dst << ", score: " << max_scored_move->first << std::endl;
#endif
  return best_move_with_scores{next_move, scored_moves};
}

scored_move HeuristicAgent::score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t) const {
  Board new_board = board.create_new_board_from_move_and_forward_to_last_move(maximizing_player, move);
  auto score = game_phase == GamePhase::END_GAME ?
               LateHeuristicValue::get_score(maximizing_player, new_board) :
               EarlyHeuristicValue::get_score(maximizing_player, new_board);

#ifdef VERBOSE_EVEN_MORE
  std::cout << "heuristic - move: " << (int)move.src << "," << (int)move.dst << ", score: " << score << std::endl;
#endif
  return scored_move{score, move};
}
