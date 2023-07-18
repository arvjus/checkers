#include <gtest/gtest.h>
#include "test-helpers.h"
#include "game.h"

TEST(game, start_game) {
  Game game{true};
  game.set_player_turn(Player::Black);

  ASSERT_FALSE(game.is_over());
  ASSERT_EQ(Player::Undef, game.get_winner());
  ASSERT_EQ(Player::Black, game.whose_turn());
}

TEST(game, game_phases) {
  Game game{true};
  game.set_player_turn(Player::Black);

  ASSERT_EQ(GamePhase::OPENING_MIDDLE_GAME, game.get_game_phase());
}

TEST(game, play_win_by_capture) {
  Game game{true};
  game.set_player_turn(Player::Black);

  std::vector<Move> non_final_moves = {
      Move(10, 14), Move(23, 18), Move(14, 23), Move(26, 19), Move(11, 15),
      Move(19, 10), Move(6, 15), Move(22, 18), Move(15, 22), Move(25, 18),
      Move(9, 13), Move(21, 17), Move(13, 22), Move(31, 26), Move(22, 31),
      Move(24, 19), Move(31, 24), Move(24, 15), Move(15, 22), Move(29, 25),
      Move(22, 29), Move(30, 25), Move(29, 22), Move(28, 24), Move(12, 16),
      Move(32, 27), Move(16, 20), Move(27, 23), Move(20, 27), Move(23, 18)
  };
  for (auto&& move: non_final_moves) {
    game.move(move);
    ASSERT_FALSE(game.is_over());
  }
  game.move(Move(22, 15));
  ASSERT_TRUE(game.is_over());
  ASSERT_EQ(Player::Black, game.get_winner());
}

TEST(game, play_win_by_no_legal_moves) {
  Game game{true};
  game.set_player_turn(Player::Black);

  std::vector<Move> non_final_moves = {
      Move(11, 15), Move(22, 18), Move(15, 22), Move(25, 18), Move(12, 16),
      Move(18, 14), Move(9, 18), Move(23, 14), Move(10, 17), Move(21, 14),
      Move(5, 9), Move(14, 5), Move(6, 9), Move(29, 25), Move(9, 13),
      Move(25, 22), Move(2, 6), Move(22, 18), Move(13, 17), Move(27, 23),
      Move(17, 21), Move(24, 19), Move(8, 12), Move(30, 25), Move(21, 30),
      Move(28, 24), Move(4, 8), Move(18, 14), Move(6, 10), Move(32, 27),
      Move(10, 17), Move(23, 18), Move(16, 23), Move(23, 32), Move(24, 19),
      Move(30, 23), Move(23, 14), Move(31, 27),
      Move(32, 23)
  };
  for (auto&& move: non_final_moves) {
    game.move(move);
    ASSERT_FALSE(game.is_over());
  }
  game.move(Move(23, 16));
  ASSERT_TRUE(game.is_over());
  ASSERT_EQ(Player::Black, game.get_winner());
}

TEST(game, play_move_limit_draw) {
  Game game{true};
  game.set_player_turn(Player::Black);

  std::vector<Move> non_final_moves = {
      Move(10, 14), Move(22, 17), Move(9, 13), Move(17, 10), Move(7, 14),
      Move(25, 22), Move(6, 10), Move(29, 25), Move(1, 6), Move(22, 18), Move(6, 9),
      Move(24, 19), Move(2, 6), Move(28, 24), Move(11, 16), Move(24, 20), Move(8, 11),
      Move(32, 28), Move(4, 8), Move(27, 24), Move(3, 7), Move(31, 27), Move(13, 17),
      Move(25, 22), Move(9, 13), Move(18, 9), Move(9, 2), Move(10, 14), Move(22, 18),
      Move(5, 9), Move(19, 15), Move(16, 19), Move(23, 16), Move(12, 19), Move(30, 25),
      Move(14, 23), Move(23, 32), Move(21, 14), Move(14, 5), Move(11, 18), Move(2, 11),
      Move(11, 4), Move(19, 23), Move(26, 19), Move(13, 17), Move(25, 21), Move(17, 22),
      Move(21, 17), Move(22, 25), Move(17, 14), Move(18, 22), Move(5, 1), Move(22, 26),
      Move(4, 8), Move(26, 31), Move(19, 15), Move(25, 30), Move(8, 11), Move(31, 26),
      Move(1, 6), Move(26, 23), Move(24, 19), Move(23, 16), Move(16, 7), Move(14, 10),
      Move(7, 14), Move(15, 10), Move(14, 7), Move(28, 24), Move(32, 28), Move(20, 16),
      Move(28, 19), Move(19, 12), Move(6, 9), Move(7, 10), Move(9, 13), Move(10, 7),
      Move(13, 9), Move(7, 3), Move(9, 6), Move(3, 7), Move(6, 1), Move(7, 11),
      Move(1, 6), Move(11, 8), Move(6, 9), Move(8, 11), Move(9, 6), Move(11, 8),
      Move(6, 9), Move(8, 11), Move(9, 6), Move(11, 8), Move(6, 9), Move(8, 11),
      Move(9, 6), Move(11, 8), Move(6, 9), Move(8, 11), Move(9, 6), Move(11, 8),
      Move(6, 9), Move(8, 11), Move(9, 6), Move(11, 8), Move(6, 9), Move(8, 11),
      Move(9, 6), Move(11, 8), Move(6, 9), Move(8, 11), Move(9, 6)
  };
  for (auto&& move: non_final_moves) {
    game.move(move);
    ASSERT_FALSE(game.is_over());
  }
  game.move(Move(11, 8));
  ASSERT_TRUE(game.is_over());
  ASSERT_EQ(Player::Undef, game.get_winner());
}

TEST(game, undo) {
  bool result;
  Game game{true};
  game.set_player_turn(Player::White);

  game.move({23, 18});
  game.move({10, 15});
  game.move({21, 17});
  game.move({9, 13});
  ASSERT_EQ(4, game.get_move_count());
  ASSERT_EQ(Player::White, game.get_board().get_piece_at_pos(17).get_player());

  result = game.undo_move();
  ASSERT_TRUE(result);
  ASSERT_EQ(2, game.get_move_count());
  ASSERT_EQ(Player::Undef, game.get_board().get_piece_at_pos(17).get_player());

  result = game.undo_move();
  ASSERT_TRUE(result);

  result = game.undo_move();
  ASSERT_FALSE(result);
}
