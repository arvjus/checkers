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
#include <filesystem>
#include <fstream>
#include "test-helpers.h"
#include "move.h"
#include "board.h"
#include "snapshot.h"

TEST(snapshot, init) {
  std::vector<std::string> pieces = {"b1", "w5", "B15", "W30"};

  Board board(false);
  board.init(pieces);
  board.set_player_turn(Player::White);

  Snapshot snapshot(board);
  ASSERT_EQ(Player::White, snapshot.whose_turn());
  ASSERT_ITERABLE_EQ(pieces, snapshot.get_pieces());
}

TEST(snapshot, save) {
  Board board(false);
  board.init({"b1", "w5", "B15", "W30"});
  board.set_player_turn(Player::White);

  auto file = std::filesystem::current_path() / "test.csv";
  if (exists(file))
    remove(file);
  Snapshot snapshot(board);
  snapshot.save(file);
  ASSERT_TRUE(exists(file));
}

TEST(snapshot, open) {
  auto file = std::filesystem::current_path() / "test.csv";
  Snapshot snapshot;
  snapshot.open(file);
  ASSERT_EQ(4, snapshot.get_pieces().size());

  Board board(false);
  board.init(snapshot.get_pieces());
  board.set_player_turn(snapshot.whose_turn());
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(1).get_player());
  ASSERT_FALSE(board.get_piece_at_pos(5).is_king());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(5).get_player());
  ASSERT_EQ(Player::Black, board.get_piece_at_pos(15).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(15).is_king());
  ASSERT_EQ(Player::White, board.get_piece_at_pos(30).get_player());
  ASSERT_TRUE(board.get_piece_at_pos(30).is_king());
  ASSERT_EQ(Player::White, board.whose_turn());
}

TEST(snapshot, get_snapshot_name) {
  auto existing_file = std::filesystem::current_path() / "snapshot_1.csv";
  if (!exists(existing_file)) {
    std::ofstream out(existing_file, std::ios::trunc);
    out.close();
  }

  auto new_file = Snapshot::get_snapshot_name();
  ASSERT_FALSE(new_file.empty());
  ASSERT_EQ(std::filesystem::current_path() / "snapshot_2.csv", new_file);
  remove(existing_file);
}
