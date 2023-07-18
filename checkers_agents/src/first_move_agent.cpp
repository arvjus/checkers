#include <set>
#include "first_move_agent.h"
#include "utils.h"

std::vector<Move> worst_moves_to_start_with = {{9, 13}, {12, 16}, {24, 20}, {21, 17}};

using first_second = std::pair<std::vector<Move>, std::vector<Move>>;
std::vector<first_second> first_second_vectors = {
    {{{9, 13}, {9, 14}, {10, 14}, {10, 15}}, {{22, 18}}},
    {{{11, 15}, {11, 16}}, {{22, 18}, {23, 18}}},
    {{{12, 16}}, {{22, 18}, {24, 20}}},
    {{{24, 20}, {24, 19}, {23, 19}, {23, 18}}, {{11, 15}}},
    {{{22, 18}, {22, 17}}, {{11, 15}, {10, 15}}},
    {{{21, 17}}, {{11, 15}, {9, 13}}}
};

FirstMoveAgent::FirstMoveAgent(Player p)
  : Agent("first_move", p) {
}

FirstMoveAgent::~FirstMoveAgent() = default;

best_move_with_scores FirstMoveAgent::search_next_move(const std::unique_ptr<Game>& game) const {
  vector_of_scored_moves empty;
  if (game->get_move_count() == 0) {
    std::vector<Move> best_moves;
    auto possible_moves = game->get_board().get_possible_moves();
    std::copy_if(possible_moves.begin(), possible_moves.end(),
                 std::back_inserter(best_moves), [](Move move) {
                   return !vector_contains(worst_moves_to_start_with, move);
                 });
    return best_move_with_scores{take_random(best_moves), empty};
  } else if (game->get_move_count() == 1) {
    Move move = opponents_first_move(game);
    for (auto vectors : first_second_vectors)
      if (vector_contains(vectors.first, move))
        return best_move_with_scores{vectors.second.at(Utils::take_random(vectors.second.size())), empty};
  }
  return best_move_with_scores{Move::none, empty};
}

Move FirstMoveAgent::opponents_first_move(const std::unique_ptr<Game>& game) const {
  assert(game->get_move_count() == 1);

  auto board = game->get_board();
  auto src = Pos::none;
  for (Pos pos : {9, 10, 11, 12, 21, 22, 23, 24})
    if (board.get_piece_at_pos(pos).get_player() == Player::Undef) {
      src = pos;
      break;
    }

  auto dst = Pos::none;
  for (Pos pos = 13; pos <= 20; pos ++)
      if (board.get_piece_at_pos(pos).get_player() != Player::Undef) {
        dst = pos;
        break;
      }

  return (src == Pos::none || dst == Pos::none) ? Move::none : Move(src, dst);
}
