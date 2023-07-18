#include <utility>
#include "agent.h"

Agent::Agent(std::string n, Player p)
  : name(std::move(n)), maximizing_player(p) {
}

Agent::~Agent() = default;

best_move_with_scores Agent::next_move(const std::unique_ptr<Game>& game) const {
  auto possible_moves = game->get_board().get_possible_moves();
  if (possible_moves.empty())
    return best_move_with_scores{Move::none, vector_of_scored_moves()};
  if (possible_moves.size() == 1)
    return best_move_with_scores{possible_moves.at(0), vector_of_scored_moves()};
  else
    return search_next_move(game);
}

best_move_with_scores Agent::search_next_move(const std::unique_ptr<Game>& game) const {
  return best_move_with_scores{Move::none, vector_of_scored_moves()};
}

Player Agent::swap(Player player) {
  return player == Player::Black ? Player::White : Player::Black;
}
