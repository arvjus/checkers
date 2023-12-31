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

#include <fstream>
#include <sstream>
#include "snapshot.h"
#include "utils.h"

Snapshot::Snapshot(const Board& b) : player_turn(b.whose_turn()) {
  for (Pos pos = 1; pos <= 32; pos ++) {
    auto piece = b.get_piece_at_pos(pos);
    if (piece.get_player() != Player::Undef)
      pieces.push_back(piece_to_string(piece));
  }
}

void Snapshot::save(std::filesystem::path path) {
  std::ofstream out(path, std::ios::trunc);
  out << std::to_string(static_cast<int>(whose_turn()));
  for (auto piece : pieces)
    out << ',' << piece;
  out << std::endl;
  out.close();
}

void Snapshot::open(std::filesystem::path path) {
  std::string line;
  std::ifstream in(path);
  if (in.is_open()) {
    getline(in, line);
    in.close();
  }

  std::string token;
  std::stringstream ss(line);
  pieces.clear();
  while (ss.good()) {
    auto first = ss.tellg() == 0l;
    getline(ss, token, ',');
    if (token.empty())
      throw std::domain_error("invalid csv format");
    if (first)
      player_turn = token.at(0) == 1 ? Player::Black : Player::White;
    else
      pieces.push_back(token);
  }
}

std::filesystem::path Snapshot::get_snapshot_name() {
  char filename[20];
  for (auto i = 1; i <= 100; i++) {
    std::snprintf(filename, sizeof(filename), "snapshot_%d.csv", i);
    auto path = std::filesystem::current_path() / filename;
    if (!exists(path))
      return path;
  }
  return std::string();
}

