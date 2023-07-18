#pragma once

#include <array>
#include <set>
#include <vector>
#include <tuple>

#include "piece.h"
#include "move.h"

class Board {
public:
  Board(bool initial_placement = true);
  void init(const std::vector<std::string>& strings);
  void set_player_turn(Player player);
  [[nodiscard]] Player whose_turn() const;
  void put_piece(Piece piece);
  [[nodiscard]] Piece get_piece_at_pos(Pos pos) const;
  [[nodiscard]] std::vector<Piece> get_available_inventory(Player player) const;
  [[nodiscard]] std::tuple<int, int, int, int> count_available_inventory(Player player) const; // pl, PL, op, OP
  [[nodiscard]] std::uint16_t count_movable_player_pieces(Player player) const;
  [[nodiscard]] std::vector<Move> get_possible_moves() const;
  [[nodiscard]] std::vector<Move> get_possible_moves(Piece piece) const;
  [[nodiscard]] std::vector<Move> get_possible_moves(Player player) const;
  [[nodiscard]] std::vector<Move> get_possible_positional_moves(Piece piece) const;
  [[nodiscard]] std::vector<Move> get_possible_positional_moves(Player player) const;
  [[nodiscard]] std::vector<Move> get_possible_capture_moves(Piece piece) const;
  [[nodiscard]] std::vector<Move> get_possible_capture_moves(Player player) const;
  [[nodiscard]] Board create_new_board_from_move(Move move) const;
  [[nodiscard]] Board create_new_board_from_move_and_forward_to_last_move(Player player, Move move) const;

  void perform_positional_move(const Move& move);
  void perform_capture_move(const Move& move);

private:
  std::array<Piece, BOARD_SIZE> pieces;
  Player player_turn = Player::Undef;
  std::vector<Move> requiring_further_capture_moves;

  template <typename T>
  std::vector<T> transform_collect(std::vector<Piece>&& in, std::vector<T> (Board::*transform_fn)(Piece) const) const;
  [[nodiscard]] std::vector<Pos> get_surrounding_positions(Piece piece, Player neighbour) const;
  void perform_move(const Move& move);
  void next_players_turn();
};

inline void Board::set_player_turn(Player player) {
  player_turn = player;
}

inline Player Board::whose_turn() const {
  return player_turn;
}

inline void Board::next_players_turn() {
  player_turn = player_turn == Player::Black ? Player::White : Player::Black;
}

inline std::vector<Move> Board::get_possible_moves() const {
  return get_possible_moves(player_turn);
}
