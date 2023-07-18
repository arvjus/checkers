#include <numeric>
#include "early_heuristic.h"
#include "utils.h"
#include "scores.h"

std::vector<Pos> middle_positions = {14, 15, 18, 19};
std::vector<Pos> back_rows_positions = {1, 3, 30, 32};

score EarlyHeuristicValue::get_score(Player player, const Board& board) {
  auto score = BasicHeuristicValue::get_score(player, board);

  auto players_inventory = board.get_available_inventory(player);
  auto opponents_inventory = board.get_available_inventory(get_opponent(player));

  // back row
  score += score_back_row_positions(players_inventory);
  score -= score_back_row_positions(opponents_inventory);

  // centrality
  score += score_middle_positions(players_inventory);
  score -= score_middle_positions(opponents_inventory);

  return score;
}

score EarlyHeuristicValue::score_back_row_positions(const std::vector<Piece>& inventory) {
  return std::transform_reduce(inventory.begin(), inventory.end(), 0, std::plus<>(),
                        [](auto piece) {
    return !piece.is_king() && vector_contains(back_rows_positions, piece.get_pos()) ? SCORE_BACK_ROW_POSITIONS : 0; });
}

score EarlyHeuristicValue::score_middle_positions(const std::vector<Piece>& inventory) {
  return std::transform_reduce(inventory.begin(), inventory.end(), 0, std::plus<>(),
                               [](auto piece) {
    return vector_contains(middle_positions, piece.get_pos()) ? SCORE_MIDDLE_POSITIONS : 0; });
}
