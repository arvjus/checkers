/* Copyright (c) 2022, Arvid Juskaitis (arvydas.juskaitis@gmail.com)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1335  USA */

#include <gtest/gtest.h>
#include "test-helpers.h"
#include "../../checkers_agents/src/early_heuristic.h"
#include "../../checkers_agents/src/late_heuristic.h"
#include "scores.h"

TEST(early_heuristic_value, no_change) {
  Board board(false);
  board.init({"b2", "W9", "b27"});
  board.set_player_turn(Player::Black);

  auto initial_score = EarlyHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({2, 7});
  auto score = EarlyHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score, score);
}

TEST(early_heuristic_value, became_a_king) {
  Board board(false);
  board.init({"b2", "W9", "b27"});
  board.set_player_turn(Player::Black);

  auto initial_score = EarlyHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({27, 32});
  auto score = EarlyHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score - SCORE_PIECE + SCORE_KING, score);
}

TEST(early_heuristic_value, to_be_captured) {
  Board board(false);
  board.init({"b2", "W9", "b27"});
  board.set_player_turn(Player::Black);

  auto initial_score = EarlyHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({2, 6});
  auto score = EarlyHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score - SCORE_POSSIBLE_CAPTURE, score);
}

TEST(early_heuristic_value, back_row_positions) {
  Board board(false);
  board.init({"b1", "b2", "w30"});
  board.set_player_turn(Player::Black);

  auto initial_score = EarlyHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({1, 6});
  auto score = EarlyHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score - SCORE_BACK_ROW_POSITIONS, score);
}

TEST(early_heuristic_value, middle_positions) {
  Board board(false);
  board.init({"b10", "w30"});
  board.set_player_turn(Player::Black);

  auto initial_score = EarlyHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({10, 15});
  auto score = EarlyHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score + SCORE_MIDDLE_POSITIONS, score);
}

TEST(late_heuristic_value, starting_player_has_the_move) {
  Board board(false);
  board.init({"b10", "w30"});
  board.set_player_turn(Player::Black);

  auto has_the_move_black = LateHeuristicValue::has_the_move(Player::Black, board);
  ASSERT_TRUE(has_the_move_black);
  auto has_the_move_white = LateHeuristicValue::has_the_move(Player::White, board);
  ASSERT_FALSE(has_the_move_white);

  auto initial_score = LateHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({10, 15});
  auto score = LateHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score + SCORE_OPPONENT_DISTANCES, score);
}

TEST(late_heuristic_value, next_player_has_the_move) {
  Board board(false);
  board.init({"b2", "w26"});
  board.set_player_turn(Player::Black);

  auto has_the_move_black = LateHeuristicValue::has_the_move(Player::Black, board);
  ASSERT_FALSE(has_the_move_black);
  auto has_the_move_white = LateHeuristicValue::has_the_move(Player::White, board);
  ASSERT_TRUE(has_the_move_white);

  auto initial_score = LateHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({2, 6});
  auto score = LateHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score + SCORE_DOUBLE_CORNER_DISTANCES, score);
}

TEST(late_heuristic_value, oponent_towards_single_corner) {
  Board board(false);
  board.init({"b2", "W5"});
  board.set_player_turn(Player::White);

  auto initial_score = LateHeuristicValue::get_score(Player::Black, board);

  board.perform_positional_move({5, 9});
  auto score = LateHeuristicValue::get_score(Player::Black, board);
  ASSERT_EQ(initial_score + SCORE_SINGLE_CORNER_DISTANCES, score);
}

