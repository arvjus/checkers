#pragma once

#include "agent.h"

class FirstMoveAgent : public Agent {
public:
  FirstMoveAgent(Player p = Player::Black);
  ~FirstMoveAgent() override;
  [[nodiscard]] Move opponents_first_move(const std::unique_ptr<Game>& game) const;

protected:
  [[nodiscard]] best_move_with_scores search_next_move(const std::unique_ptr<Game>& game) const override;
};