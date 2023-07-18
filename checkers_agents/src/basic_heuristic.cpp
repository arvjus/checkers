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
