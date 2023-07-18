#include <iostream>
#include <ctime>
#include <climits>
#include "checkers_config.h"
#include "utils.h"
#include "early_heuristic.h"
#include "late_heuristic.h"
#include "minmax_agent.h"

MinmaxAgent::MinmaxAgent(int m_duration, int m_depth, Player p)
  : HeuristicAgent(m_duration, "minmax", p), max_depth(m_depth) {
}

MinmaxAgent::~MinmaxAgent() = default;

scored_move MinmaxAgent::score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const {
  assert(board.whose_turn() == maximizing_player);

  Board new_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
  uint32_t count = 0;
  auto score = minmax(game_phase, new_board, max_depth - 1, false, timeout, count);

#ifdef VERBOSE_EVEN_MORE
  std::cout << name + " - move: " << (int)move.src << "," << (int)move.dst << ", score: " << score << ", count: " << count << std::endl;
#endif
  return scored_move{score, move};
}

score MinmaxAgent::minmax(GamePhase game_phase, const Board& board, int depth, bool maximizing, uint32_t timeout, uint32_t& count) const {
  count++;

  auto possible_moves = board.get_possible_moves();
  if (time(nullptr) > timeout || depth == 0 || possible_moves.empty())
    return game_phase == GamePhase::END_GAME ?
           LateHeuristicValue::get_score(maximizing_player, board) :
           EarlyHeuristicValue::get_score(maximizing_player, board);

  if (maximizing) {
    score value = LONG_MIN;
    for (auto move : possible_moves) {
      auto child_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
      value = std::max(value, minmax(game_phase, child_board, depth - 1, false, timeout, count));
    }
    return value;
  } else {
    score value = LONG_MAX;
    for (auto move : possible_moves) {
      auto child_board = board.create_new_board_from_move_and_forward_to_last_move(board.whose_turn(), move);
      value = std::min(value, minmax(game_phase, child_board, depth - 1, true, timeout, count));
    }
    return value;
  }
}
