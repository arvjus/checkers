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
