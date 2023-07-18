#pragma once

#include "heuristic_agent.h"

class AlphabetaAgent : public HeuristicAgent {
public:
  AlphabetaAgent(int m_duration, int m_depth, Player p = Player::Black);
  ~AlphabetaAgent() override;
  [[nodiscard]] scored_move score_move(GamePhase game_phase, const Board& board, const Move& move, uint32_t timeout) const override;

protected:
  const int max_depth;

  score alphabeta(GamePhase game_phase, const Board &board, int depth, bool maximizing, score alpha, score beta, uint32_t timeout, uint32_t& count) const;
};