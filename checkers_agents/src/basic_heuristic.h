#pragma once

#include "board.h"

class BasicHeuristicValue {
public:
  [[nodiscard]] static score get_score(Player player, const Board& board);
  [[nodiscard]] static Player get_opponent(const Player &player);

protected:
};