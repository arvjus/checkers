#pragma once

#include <memory>
#include "game.h"

using scored_move = std::pair<score, Move>;
using vector_of_scored_moves = std::vector<scored_move>;
using best_move_with_scores = std::pair<Move, vector_of_scored_moves>;

class Agent {
public:
  Agent(std::string n, Player p = Player::Black);
  [[nodiscard]] virtual best_move_with_scores next_move(const std::unique_ptr<Game>& game) const final;
  virtual ~Agent();

protected:
  const std::string name;
  const Player maximizing_player;

  [[nodiscard]] virtual best_move_with_scores search_next_move(const std::unique_ptr<Game>& game) const;
  static Player swap(Player player);
};