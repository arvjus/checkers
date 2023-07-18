#include <stdexcept>
#include <cassert>
#include <cctype>
#include "piece.h"

Piece::Piece() : databits(0) {
}

Piece::Piece(Pos pos, Player player, bool king) : databits((pos - 1) & BITMASK_POS) {
  ASSERT_POS(pos);
  databits |= ((static_cast<std::uint8_t>(player) << 6) & BITMASK_PLAYER);
  if (king || is_on_king_row())
    databits |= BITMASK_KING;
}

bool Piece::operator==(const Piece& piece) const {
  return databits == piece.databits;
}

Player Piece::get_player() const {
  switch ((databits & BITMASK_PLAYER) >> 6) {
    case 1:
      return Player::Black;
    case 2:
      return Player::White;
    default:
      return Player::Undef;
  }
}

bool Piece::is_on_king_row() const {
  return (get_player() == Player::Black && get_pos().get_row() == 8) ||
         (get_player() == Player::White && get_pos().get_row() == 1);
}

bool Piece::is_king() const { return (databits & BITMASK_KING); }

Pos Piece::get_pos() const { return (databits & BITMASK_POS) + 1; }

void Piece::move(Pos pos) {
  ASSERT_POS(pos);
  databits &= ~BITMASK_POS;
  databits |= (pos - 1);
  if (is_on_king_row())
    databits |= BITMASK_KING;
}

Piece Piece::create(std::string str) {
  if (str.length() < 2)
    throw std::invalid_argument("invalid player notation");

  Player player;
  bool king = false;
  switch ((char) str.at(0)) {
    case 'B':
      king = true;
//      [[fallthrough]];
    case 'b':
      player = Player::Black;
      break;
    case 'W':
      king = true;
//      [[fallthrough]];
    case 'w':
      player = Player::White;
      break;
    default:
      throw std::invalid_argument("invalid player indicator");
  }

  if (!std::isdigit(str.at(1)))
    throw std::invalid_argument("invalid player position");

  return {static_cast<Pos>(std::stoi(& str.at(1))), player, king};
}
