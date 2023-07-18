#pragma once

#include <vector>
#include "defines.h"

class Pos {
public:
  Pos(std::uint8_t p);
  operator std::uint8_t() const;
  std::uint8_t operator ++(int);
  [[nodiscard]] std::uint16_t get_index() const;
  [[nodiscard]] Row get_row() const;
  [[nodiscard]] Col get_col() const;
  [[nodiscard]] Col get_col8() const;
  [[nodiscard]] bool on_edge() const;
  [[nodiscard]] std::uint8_t get_distance_to(Pos other) const;

  static bool is_valid(std::uint8_t pos);
  static Pos none;

private:
  std::uint8_t pos;
  static std::vector<uint8_t> edges;
};
