#pragma once

#include <algorithm>
#include "move.h"
#include "piece.h"

class Utils {
public:
  Utils();
  static int take_random(size_t max);

private:
  static Utils instance;
};

template <typename T>
inline const T& take_random(const std::vector<T>& vector) {
  return vector.at(Utils::take_random(vector.size()));
};

template <typename T>
inline bool vector_contains(const std::vector<T>& vector, const T& element) {
  return std::find(vector.begin(), vector.end(), element) != vector.end();
};

score interpolate(score in_value, score in_min, score in_max, short out_min, short out_max);
std::string move_to_string(const Move& move);
std::string piece_to_string(const Piece& piece);

