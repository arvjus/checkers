#pragma once

#include <cmath>
#include <string>
#include "pos.h"

static const std::uint8_t BITMASK_PLAYER = 0b11000000;
static const std::uint8_t BITMASK_KING = 0b00100000;
static const std::uint8_t BITMASK_POS = 0b00011111;

class Piece {
public:
  Piece();
  Piece(Pos pos, Player p = Player::Undef, bool king = false);
  bool operator==(const Piece& piece) const;
  [[nodiscard]] Player get_player() const;
  [[nodiscard]] bool is_on_king_row() const;
  [[nodiscard]] bool is_king() const;
  [[nodiscard]] Pos get_pos() const;
  void move(Pos pos);

  static Piece create(std::string str);

private:
  std::uint8_t databits;
};

static_assert(sizeof(Piece) == 1, "invalid Piece size");
