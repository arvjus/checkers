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

#pragma once

#include <string>
#include "piece.h"
#include "move.h"

#define ASSERT_ITERABLE_EQ(expected, actual) \
  ASSERT_EQ((expected).size(), (actual).size()); \
  for (unsigned int i = 0; i < (expected).size(); i++) \
    ASSERT_EQ((expected)[i], (actual)[i])

#define ASSERT_ITERABLE_EQ_WRAP_FN(expected, actual, fn) \
  ASSERT_EQ((expected).size(), (actual).size()); \
  for (unsigned int i = 0; i < (expected).size(); i++) \
    ASSERT_EQ(fn((expected)[i]), fn((actual)[i]))

#define DUMP_VECTOR_FN(v, fn) \
  std::cout << std::endl; \
  for (auto item: (v))\
    std::cout << fn(item) << std::endl
