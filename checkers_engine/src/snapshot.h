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
