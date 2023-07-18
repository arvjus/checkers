#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include "defines.h"
#include "board.h"

class Snapshot {
public:
  Snapshot();
  Snapshot(const Board& b);
  void save(std::filesystem::path fn);
  void open(std::filesystem::path fn);
  [[nodiscard]] const std::vector<std::string>&& get_pieces() const;
  [[nodiscard]] Player whose_turn() const;
  [[nodiscard]] static std::filesystem::path get_snapshot_name();

private:
  std::vector<std::string> pieces;
  Player player_turn = Player::Undef;
};

inline Snapshot::Snapshot() {
}

inline const std::vector<std::string>&& Snapshot::get_pieces() const {
  return std::move(pieces);
}

inline Player Snapshot::whose_turn() const {
  return Player::White;
}
