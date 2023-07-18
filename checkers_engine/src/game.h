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

#include "board.h"
#include "game_state.h"

enum class GamePhase {
  OPENING_MIDDLE_GAME,
  END_GAME
};

class Game {
  friend class GameState;

public:
  explicit Game(bool with_starting_pieces = true);

  void set_player_turn(Player player);
  void init_board(const std::vector<std::string>& strings);
  [[nodiscard]] Player whose_turn() const;
  void put_piece(Piece piece);
  void move(const Move& move);
  bool undo_move();
  [[nodiscard]] std::uint16_t get_move_count() const;
  [[nodiscard]] const Board& get_board() const;
  [[nodiscard]] GamePhase get_game_phase() const;
  [[nodiscard]] bool is_over() const;
  [[nodiscard]] Player get_winner() const;
  [[nodiscard]] std::vector<Pos> get_available_positions_from(Pos pos) const;
  void print_status() const;

private:
  Board board;
  std::uint16_t move_count = 0;
  std::uint16_t move_count_since_last_capture = 0;
  game_state_vector move_history;

  [[nodiscard]] bool move_limit_reached() const;
};

inline void Game::init_board(const std::vector<std::string>& strings) {
  board.init(strings);
}

inline void Game::set_player_turn(Player player) {
  board.set_player_turn(player);
}

inline Player Game::whose_turn() const {
  return board.whose_turn();
}

inline std::uint16_t Game::get_move_count() const {
  return move_count;
}

inline void Game::put_piece(Piece piece) {
  board.put_piece(piece);
}

inline const Board& Game::get_board() const {
  return board;
}

inline bool Game::move_limit_reached() const {
  return move_count_since_last_capture >= CONSECUTIVE_NON_CAPTURE_MOVE_LIMIT;
}
