#include <chrono>
#include "utils.h"
#include "move.h"
#include "piece.h"

Utils Utils::instance;

Utils::Utils() {
  std::srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int Utils::take_random(size_t max) {
  return std::rand() % max;
}

std::string move_to_string(const Move& move) {
  char buf[10];
  snprintf(buf, sizeof(buf), "%d->%d",
           static_cast<int>(move.src),
           static_cast<int>(move.dst));
  return {buf};
}

std::string piece_to_string(const Piece& piece) {
  char buf[10];
  char player = piece.get_player() == Player::Black ? 'b' : 'w';
  snprintf(buf, sizeof(buf), "%c%d",
           piece.is_king() ? toupper(player) : player,
           static_cast<int>(piece.get_pos()));
  return {buf};
}

score interpolate(score in_value, score in_min, score in_max, short out_min, short out_max) {
  if (in_min == in_max)
    return out_min;

  double f = double(in_value - in_min) / double(in_max - in_min);
  return static_cast<score>(out_min + (out_max - out_min) * f);
}
