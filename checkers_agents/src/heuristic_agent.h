#pragma once

#include "agent.h"
#include "game.h"

class HeuristicAgent : public Agent {
public:
  HeuristicAgent(int md, std::string n = "heuristic", Player p = Player::Black);
  ~HeuristicAgent() override;
  [[nodiscard]] virtual scored_move score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const;

protected:
  const int max_duration;
  std::vector<scored_move> scored_moves;

  [[nodiscard]] best_move_with_scores search_next_move(const std::unique_ptr<Game>& game) const override;
};