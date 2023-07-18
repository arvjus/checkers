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