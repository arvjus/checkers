#pragma once

#include "basic_heuristic.h"

class EarlyHeuristicValue : public BasicHeuristicValue {
public:
  [[nodiscard]] static score get_score(Player player, const Board& board);

protected:
  [[nodiscard]] static score score_back_row_positions(const std::vector<Piece>& inventory);
  [[nodiscard]] static score score_middle_positions(const std::vector<Piece>& inventory);
};