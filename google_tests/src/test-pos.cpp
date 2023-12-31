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
#include "pos.h"

TEST(pos, basic) {
  Pos pos(10);
  ASSERT_EQ(10, pos);
  ASSERT_EQ(9, pos.get_index());
}

TEST(pos, row_col) {
  Pos pos1(1);
  ASSERT_EQ(1, pos1.get_row());
  ASSERT_EQ(1, pos1.get_col());

  Pos pos15(15);
  ASSERT_EQ(4, pos15.get_row());
  ASSERT_EQ(3, pos15.get_col());

  Pos pos32(32);
  ASSERT_EQ(8, pos32.get_row());
  ASSERT_EQ(4, pos32.get_col());
}

struct item {
  Pos p1, p2;
  int exp;
};

TEST(pos, distance) {
  auto items = {
      item{1, 28, 6},
      item{4, 31, 7},
      item{29, 13, 4},
      item{29, 14, 4},
      item{29, 31, 4},
      item{29, 25, 1},
      item{29, 22, 2},
      item{26, 3, 6},
      item{22, 8, 4},
  };

  for (auto item : items) {
    ASSERT_EQ(item.exp, item.p1.get_distance_to(item.p2));
  }
}
