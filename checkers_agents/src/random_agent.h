#pragma once

#include "agent.h"

class RandomAgent : public Agent {
public:
  RandomAgent(Player p = Player::Black);
  ~RandomAgent() override;

protected:
  [[nodiscard]] best_move_with_scores search_next_move(const std::unique_ptr<Game>& g) const override;
};