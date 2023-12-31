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
#include "piece.h"

TEST(piece, defaults) {
  Piece piece;
  ASSERT_EQ(1, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::Undef, piece.get_player());
}

TEST(piece, emptyPosition) {
  Piece piece(1);
  ASSERT_EQ(1, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::Undef, piece.get_player());

  piece.move(15);
  ASSERT_EQ(15, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::Undef, piece.get_player());

  piece.move(32);
  ASSERT_EQ(32, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::Undef, piece.get_player());
}

TEST(piece, blackMan) {
  Piece piece(5, Player::Black);
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::Black, piece.get_player());

  piece.move(30);
  ASSERT_EQ(30, piece.get_pos());
  ASSERT_TRUE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::Black, piece.get_player());

  piece.move(1);
  ASSERT_EQ(1, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::Black, piece.get_player());
}

TEST(piece, blackKing) {
  Piece piece(5, Player::Black, true);
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::Black, piece.get_player());

  piece.move(30);
  ASSERT_EQ(30, piece.get_pos());
  ASSERT_TRUE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::Black, piece.get_player());
}

TEST(piece, whiteMan) {
  Piece piece(30, Player::White);
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_FALSE(piece.is_king());
  ASSERT_EQ(Player::White, piece.get_player());

  piece.move(2);
  ASSERT_EQ(2, piece.get_pos());
  ASSERT_TRUE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::White, piece.get_player());

  piece.move(25);
  ASSERT_EQ(25, piece.get_pos());
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::White, piece.get_player());
}

TEST(piece, whiteKing) {
  Piece piece(25, Player::White, true);
  ASSERT_FALSE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::White, piece.get_player());

  piece.move(2);
  ASSERT_EQ(2, piece.get_pos());
  ASSERT_TRUE(piece.is_on_king_row());
  ASSERT_TRUE(piece.is_king());
  ASSERT_EQ(Player::White, piece.get_player());
}

TEST(piece, create) {
  Piece p1 = Piece::create("b1");
  ASSERT_EQ(Player::Black, p1.get_player());

  Piece p2 = Piece::create("B15");
  ASSERT_EQ(Player::Black, p2.get_player());
  ASSERT_TRUE(p2.is_king());

  Piece p3 = Piece::create("w4");
  ASSERT_EQ(Player::White, p3.get_player());
  ASSERT_TRUE(p3.is_king());

  Piece p4 = Piece::create("W30");
  ASSERT_EQ(Player::White, p4.get_player());
  ASSERT_TRUE(p4.is_king());
}

TEST(piece, createWithErrors) {
  ASSERT_THROW(Piece::create("a"), std::invalid_argument);
  ASSERT_THROW(Piece::create("w"), std::invalid_argument);
}
