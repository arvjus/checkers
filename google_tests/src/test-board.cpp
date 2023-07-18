
#include <gtest/gtest.h>
#include "test-helpers.h"
#include "move.h"
#include "board.h"
#include "utils.h"

TEST(board, initialPlacements) {
  Board board;

  ASSERT_EQ(Player::Black, board.get_piece_at_pos(1).get_player());
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(12).get_player());
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(13).get_player());
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(20).get_player());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(21).get_player());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(32).get_player());
  ASSERT_EQ(32, board.get_piece_at_pos(32).get_pos());
}

TEST(board, noInitialPlacements) {
  Board board(false);

  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(1).get_player());
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(13).get_player());
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(20).get_player());
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(32).get_player());
  ASSERT_EQ(32, board.get_piece_at_pos(32).get_pos());
}

TEST(board, initCustom) {
  Board board(false);
  board.init({"b1", "B15", "w4", "W30"});

  ASSERT_EQ(Player::Black, board.get_piece_at_pos(1).get_player());
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(15).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(15).is_king());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(4).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(4).is_king());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(30).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(30).is_king());
}

TEST(board, positional_move) {
  Board board(false);
  board.init({"B15"});
  board.set_player_turn(Player::Black);

  board.perform_positional_move(Move(15, 10));
  ASSERT_EQ(Player::Undef, board.get_piece_at_pos(15).get_player());
  ASSERT_FALSE(board.get_piece_at_pos(15).is_king());
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(10).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(10).is_king());
}

TEST(board, capture) {
  Board board(false);
  board.init({"B1", "w6"});
  board.set_player_turn(Player::Black);

  board.perform_capture_move(Move(1, 10));
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(10).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(10).is_king());
  ASSERT_EQ(10, board.get_piece_at_pos(10).get_pos());
  ASSERT_EQ(board.get_piece_at_pos(1), board.get_piece_at_pos(1).get_pos());
  ASSERT_EQ(board.get_piece_at_pos(6), board.get_piece_at_pos(6).get_pos());
}

TEST(board, get_available_inventory) {
  Board board(false);
  board.init({"b1", "b4", "B15", "W30"});

  std::vector<Piece> expected_black = {
      Piece(1, Player::Black),
      Piece(4, Player::Black),
      Piece(15, Player::Black, true)
  };
  auto black = board.get_available_inventory(Player::Black);
  ASSERT_ITERABLE_EQ_WRAP_FN(expected_black, black, piece_to_string);

  std::vector<Piece> expected_white = {
      Piece(30, Player::White, true)
  };
  auto white = board.get_available_inventory(Player::White);
  ASSERT_ITERABLE_EQ_WRAP_FN(expected_white, white, piece_to_string);
}

TEST(board, get_possible_positional_moves_single_piece) {
  Board board(false);
  board.init({"b1", "B8", "W25", "w32"});

  auto piece_b1 = board.get_piece_at_pos(1);
  auto moves_b1 = board.get_possible_positional_moves(piece_b1);
  std::vector<Move> moves_b1_expected = {
      Move(1, 5),
      Move(1, 6)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(moves_b1_expected, moves_b1, move_to_string);

  auto piece_B8 = board.get_piece_at_pos(8);
  auto moves_B8 = board.get_possible_positional_moves(piece_B8);
  std::vector<Move> moves_B8_expected = {
      Move(8, 12),
      Move(8, 11),
      Move(8, 4),
      Move(8, 3)

  };
  ASSERT_ITERABLE_EQ_WRAP_FN(moves_B8_expected, moves_B8, move_to_string);

  auto piece_W25 = board.get_piece_at_pos(25);
  auto moves_W25 = board.get_possible_positional_moves(piece_W25);
  std::vector<Move> moves_W25_expected = {
      Move(25, 21),
      Move(25, 22),
      Move(25, 29),
      Move(25, 30)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(moves_W25_expected, moves_W25, move_to_string);

  auto piece_w32 = board.get_piece_at_pos(32);
  auto moves_w32 = board.get_possible_positional_moves(piece_w32);
  std::vector<Move> moves_w32_expected = {
      Move(32, 28),
      Move(32, 27)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(moves_w32_expected, moves_w32, move_to_string);
}

TEST(board, get_possible_positional_moves_bugfix) {
  Board board(false);
  board.init({"b1", "w29"});

  auto piece_w29 = board.get_piece_at_pos(29);
  auto moves_w29 = board.get_possible_positional_moves(piece_w29);
  std::vector<Move> moves_w29_expected = {
      Move(29, 25)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(moves_w29_expected, moves_w29, move_to_string);
}

TEST(board, get_possible_positional_moves_initial) {
  Board board;

  auto black_available = board.get_possible_positional_moves(Player::Black);
  ASSERT_EQ(7, black_available.size());

  auto white_available = board.get_possible_positional_moves(Player::White);
  ASSERT_EQ(7, white_available.size());
}

TEST(board, get_possible_positional_moves) {
  Board board(false);
  board.init({"b1", "B8", "W25", "w32"});

  auto black_available = board.get_possible_positional_moves(Player::Black);
  std::vector<Move> black_available_expected = {
      Move(1, 5),
      Move(1, 6),
      Move(8, 12),
      Move(8, 11),
      Move(8, 4),
      Move(8, 3)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(black_available_expected, black_available, move_to_string);

  auto white_available = board.get_possible_positional_moves(Player::White);
  std::vector<Move> white_available_expected = {
      Move(25, 21),
      Move(25, 22),
      Move(25, 29),
      Move(25, 30),
      Move(32, 28),
      Move(32, 27)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(white_available_expected, white_available, move_to_string);
}

TEST(board, get_possible_capture_moves) {
  Board board(false);
  board.init({"b1", "w6", "w11", "b8", "w30", "w27", "b25", "b24"});

  auto black_available = board.get_possible_capture_moves(Player::Black);
  std::vector<Move> black_available_expected = {
      Move(1, 10),
      Move(8, 15),
      Move(24, 31)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(black_available_expected, black_available, move_to_string);

  auto white_available = board.get_possible_capture_moves(Player::White);
  std::vector<Move> white_available_expected = {
      Move(11, 4),
      Move(27, 20),
      Move(30, 21)
  };
  ASSERT_ITERABLE_EQ_WRAP_FN(white_available_expected, white_available, move_to_string);
}

TEST(board, get_possible_capture_moves_out_of_range_black) {
  Board board(false);
  board.init({"b9", "b25", "b16", "w13", "w30", "w20"});

  auto black_available = board.get_possible_capture_moves(Player::Black);
  ASSERT_EQ(0, black_available.size());
}

TEST(board, get_possible_capture_moves_out_of_range_white) {
  Board board(false);
  board.init({"W6", "W26", "b30", "b1"});

  auto white_available = board.get_possible_capture_moves(Player::White);
  ASSERT_EQ(0, white_available.size());
}

TEST(board, get_possible_moves) {
  Board board(false);
  board.init({"W6", "W26", "b30", "b1"});

  auto white_available = board.get_possible_capture_moves(Player::White);
  ASSERT_EQ(0, white_available.size());
}

TEST(board, became_a_king) {
  Board board(false);
  board.init({"b22", "w26", "w27"});
  board.set_player_turn(Player::Black);

  auto black_available = board.get_possible_capture_moves(Player::Black);
  ASSERT_EQ(1, black_available.size());
  board.perform_capture_move({22, 31});
  ASSERT_EQ(Player::White, board.whose_turn());
}

TEST(board, create_new_board_from_move_and_forward_to_last_move) {
  Board board(false);
  board.init({"B21", "w25", "w26", "b14", "w17"});
  board.set_player_turn(Player::Black);

  auto new_board = board.create_new_board_from_move_and_forward_to_last_move(Player::Black, {21, 30});
  auto counts = new_board.count_available_inventory(Player::Black);
  ASSERT_EQ(1, get<0>(counts));
  ASSERT_EQ(1, get<1>(counts));
  ASSERT_EQ(1, get<2>(counts));
  ASSERT_EQ(0, get<3>(counts));
}
