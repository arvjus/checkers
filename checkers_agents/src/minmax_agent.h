#pragma once

#include "heuristic_agent.h"

class MinmaxAgent : public HeuristicAgent {
public:
  MinmaxAgent(int m_duration, int m_depth, Player p = Player::Black);
  ~MinmaxAgent() override;
  [[nodiscard]] scored_move score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const override;

protected:
  const int max_depth;

  score minmax(GamePhase game_phase, const Board &board, int depth, bool maximizing, uint32_t timeout, uint32_t& count) const;
};