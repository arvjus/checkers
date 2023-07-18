#include "random_agent.h"
#include "utils.h"

RandomAgent::RandomAgent(Player p)
    : Agent("random", p) {
}

best_move_with_scores RandomAgent::search_next_move(const std::unique_ptr<Game>& game) const {
  auto possible_moves = game->get_board().get_possible_moves();
  assert(possible_moves.size() > 1);
  return best_move_with_scores{take_random(possible_moves), vector_of_scored_moves()};
}

RandomAgent::~RandomAgent() = default;
