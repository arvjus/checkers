#include <cmath>
#include "pos.h"
#include "utils.h"

Pos Pos::none = 0;

std::vector<uint8_t> Pos::edges = {4, 5, 12, 13, 20, 21, 28, 29};

Pos::Pos(std::uint8_t p) : pos(p) {
}

std::uint8_t Pos::operator++(int) {
  return pos ++;
}

Pos::operator std::uint8_t() const {
  return pos;
}

std::uint16_t Pos::get_index() const {
  return pos - 1;
}

Row Pos::get_row() const {
  return static_cast<Row>((pos - 1) / BOARD_WIDTH + 1);
}

Col Pos::get_col() const { return (pos - 1) % BOARD_WIDTH + 1; }

Col Pos::get_col8() const {
  return (pos - 1) % BOARD_WIDTH * 2 + get_row() % 2 + 1;
}

std::uint8_t Pos::get_distance_to(Pos other) const {
  auto dist = std::max(abs(get_row() - other.get_row()), abs(get_col8() - other.get_col8()));
  return static_cast<std::uint8_t>(dist);
}

bool Pos::on_edge() const {
  return vector_contains(edges, pos);
}

bool Pos::is_valid(std::uint8_t pos) {
  return pos >= 1 && pos <= 32;
}
