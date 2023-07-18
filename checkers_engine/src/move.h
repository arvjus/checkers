#pragma once

#include "pos.h"
#include <cassert>

struct Move {
  Move(Pos s, Pos d);
  bool operator==(const Move& rhs) const;
  bool is_capture_move() const;

  static Move none;
  Pos src;
  Pos dst;
};

inline Move::Move(Pos s, Pos d) : src(s), dst(d) {
  ASSERT_POS(src);
  ASSERT_POS(dst);
  assert(src != dst);
}

inline bool Move::operator==(const Move& rhs) const {
  return src == rhs.src && dst == rhs.dst;
}

inline bool Move::is_capture_move() const {
  auto dist = std::abs(src - dst);
  return dist == 7 || dist == 9;
}

inline Move Move::none {1, 32};


