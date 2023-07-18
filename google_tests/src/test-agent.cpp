#include <gtest/gtest.h>
#include "test-helpers.h"
#include "../../checkers_agents/src/random_agent.h"
#include "../../checkers_agents/src/first_move_agent.h"
#include "utils.h"

TEST(agent, single_move) {
  std::unique_ptr<Game> game = std::make_unique<Game>(false);
  game->set_player_turn(Player::White);
  game->put_piece({28, Player::Black});
  game->put_piece({32, Player::White});

  Agent agent("agent", Player::White);
  auto next_move = agent.next_move(game);
  ASSERT_EQ(Move(32, 27), next_move.first);
}

TEST(agent, multiple_moves) {
  std::unique_ptr<Game> game = std::make_unique<Game>(false);
  game->set_player_turn(Player::Black);
  game->put_piece({24, Player::Black});
  game->put_piece({32, Player::White});

  Agent agent("agent", Player::Black);
  auto next_move = agent.next_move(game);
  ASSERT_EQ(Move::none, next_move.first);
}

TEST(agent, multiple_moves_random) {
  std::unique_ptr<Game> game = std::make_unique<Game>(false);
  game->set_player_turn(Player::Black);
  game->put_piece({24, Player::Black});
  game->put_piece({32, Player::White});

  RandomAgent agent;
  auto next_move = agent.next_move(game);
  ASSERT_NE(Move::none, next_move.first);
}

TEST(agent, first_move) {
  std::unique_ptr<Game> game = std::make_unique<Game>();
  game->set_player_turn(Player::Black);

  FirstMoveAgent agent;
  auto next_move = agent.next_move(game);
  ASSERT_NE(Move(9, 13), next_move.first);
  ASSERT_NE(Move(12, 16), next_move.first);
}

TEST(agent, second_move) {
  std::unique_ptr<Game> game = std::make_unique<Game>();
  game->set_player_turn(Player::White);
  game->move({22, 18});

  FirstMoveAgent agent;
  Move first_move = agent.opponents_first_move(game);
  ASSERT_EQ(Move(22, 18), first_move);

  auto next_move = agent.next_move(game);
  std::vector<Move> excpeted_next_move{{11, 15}, {10, 15}};
  ASSERT_TRUE(vector_contains(excpeted_next_move, next_move.first));
}
