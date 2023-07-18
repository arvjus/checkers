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

#include <iostream>
#include "board.h"
#include "utils.h"

Board::Board(bool initial_placement) : player_turn(Player::Undef) {
  for (unsigned short i = 1; i <= BOARD_SIZE; i++) {
    Player player = Player::Undef;
    if (initial_placement) {
      if (i <= INITIAL_NUMBER_OF_PIECES_PER_PLAYER)
        player = Player::Black;
      else if (i > BOARD_SIZE - INITIAL_NUMBER_OF_PIECES_PER_PLAYER)
        player = Player::White;
    }
    Piece piece(i, player);
    pieces[piece.get_pos().get_index()] = piece;
  }
}

void Board::init(const std::vector<std::string>& strings) {
  for (const auto& str : strings) {
    auto piece = Piece::create(str);
    pieces[piece.get_pos().get_index()] = piece;
  }
}

void Board::put_piece(Piece piece) {
  ASSERT_POS(piece.get_pos());
  pieces[piece.get_pos().get_index()] = piece;
}

Piece Board::get_piece_at_pos(Pos pos) const {
  ASSERT_POS(pos);
  return pieces[pos.get_index()];
}

std::vector<Piece> Board::get_available_inventory(const Player player) const {
  std::vector<Piece> inventory;
  std::copy_if(
      pieces.begin(), pieces.end(), std::back_inserter(inventory),
      [&player](const Piece& piece) { return piece.get_player() == player; });
  return inventory;
}

// pl, PL, op, OP
std::tuple<int, int, int, int> Board::count_available_inventory(const Player player) const {
  auto counts = std::make_tuple( 0, 0, 0, 0);
  auto opponent = player == Player::Black ? Player::White : Player::Black;
  for (Piece piece : pieces)
    if (piece.get_player() == player) {
      if (piece.is_king())
        get<1>(counts) ++;
      else
        get<0>(counts) ++;
    }
    else
    if (piece.get_player() == opponent) {
      if (piece.is_king())
        get<3>(counts) ++;
      else
        get<2>(counts) ++;
    }
  return counts;
}

std::uint16_t Board::count_movable_player_pieces(const Player player) const {
  return get_possible_capture_moves(player).size() +
         get_possible_positional_moves(player).size();
}

std::vector<Move> Board::get_possible_moves(Piece piece) const {
  auto moves = get_possible_capture_moves(piece);
  if (moves.empty())
    moves = get_possible_positional_moves(piece);
  return moves;
}

std::vector<Move> Board::get_possible_moves(Player player) const {
  auto moves = get_possible_capture_moves(player);
  if (moves.empty())
    moves = get_possible_positional_moves(player);
  return moves;
}

std::vector<Move> Board::get_possible_positional_moves(const Piece piece) const {
  auto moves = std::vector<Move>();
  auto src = piece.get_pos();
  for (auto&& dst : get_surrounding_positions(piece, Player::Undef))
    moves.emplace_back(src, dst);

  return moves;
}

std::vector<Move> Board::get_possible_positional_moves(Player player) const {
  return transform_collect(get_available_inventory(player),
                           & Board::get_possible_positional_moves);
}

std::vector<Move> Board::get_possible_capture_moves(const Piece piece) const {
  std::vector<Move> moves;
  auto pos = piece.get_pos();
  auto odd_row = pos.get_row() % 2;
  auto even_row = pos.get_row() % 2 == 0;

  for (auto opponent : get_surrounding_positions(
           piece, piece.get_player() == Player::Black ? Player::White
                                                      : Player::Black)) {
    if ((opponent.get_row() % 2 == 0 && opponent.get_col() == 1) ||
        (opponent.get_row() % 2 && opponent.get_col() == 4))
      continue;

    auto opponent_dist = opponent - pos;
    auto jump = (even_row && (opponent_dist == 4 || opponent_dist == -5)) ||
                        (odd_row && (opponent_dist == -4 || opponent_dist == 5))
                    ? 9 : 7;
    auto dst = pos + (jump * (opponent_dist > 0 ? 1 : -1));
    if (Pos::is_valid(dst) &&
        pieces[Pos(dst).get_index()].get_player() == Player::Undef)
      moves.emplace_back(pos, dst);
  }
  return moves;
}

std::vector<Move> Board::get_possible_capture_moves(const Player player) const {
  if (!requiring_further_capture_moves.empty())
    return requiring_further_capture_moves;

  auto inventory = get_available_inventory(player);
  return transform_collect(std::move(inventory), &Board::get_possible_capture_moves);
}

template <typename T>
std::vector<T>
Board::transform_collect(std::vector<Piece> &&in, std::vector<T> (Board::*transform_fn)(Piece) const) const {
  auto out = std::vector<T>();
  for (auto&& in_item : in) {
    auto fn_result = (this->*transform_fn)(in_item);
    out.insert(out.end(), fn_result.begin(), fn_result.end());
  }
  return out;
}

void Board::perform_positional_move(const Move& move) {
  assert(!move.is_capture_move());

  perform_move(move);
  next_players_turn();
}

void Board::perform_capture_move(const Move& move) {
  assert(move.is_capture_move());

  auto piece_src = pieces[move.src.get_index()];
  auto was_a_king = piece_src.is_king();
  perform_move(move);

  // do capture
  auto dist = move.dst - move.src;
  // clang-format off
  if (move.src.get_row() % 2)
    // odd
    switch (dist) {
      case -9: dist = -4; break;
      case -7: dist = -3; break;
      case  9: dist =  5; break;
      case  7: dist =  4; break;
      default: assert(false);
    }
  else // even
    switch (dist) {
      case -9: dist = -5; break;
      case -7: dist = -4; break;
      case  9: dist =  4; break;
      case  7: dist =  3; break;
      default: assert(false);
    }
  // clang-format on
  Pos captured(move.src + dist);
  pieces[captured.get_index()] = captured;

  // further captures
  auto piece_dst = pieces[move.dst.get_index()];
  if (piece_dst.is_king() != was_a_king)
    requiring_further_capture_moves.clear();
  else
    requiring_further_capture_moves = get_possible_capture_moves(piece_dst);
  if (requiring_further_capture_moves.empty())
    next_players_turn();
}

Board Board::create_new_board_from_move(Move move) const {
  auto new_board = *this;
  if (move.is_capture_move())
    new_board.perform_capture_move(move);
  else
    new_board.perform_positional_move(move);
  return new_board;
}

Board Board::create_new_board_from_move_and_forward_to_last_move(Player player, Move move) const {
  assert(vector_contains(get_possible_moves(), move));
  auto new_board = create_new_board_from_move(move);
  auto possible_capture_moves = new_board.get_possible_capture_moves(new_board.whose_turn());
  while (!possible_capture_moves.empty() && new_board.whose_turn() == player) {
    new_board = new_board.create_new_board_from_move(take_random(possible_capture_moves));
    possible_capture_moves = new_board.get_possible_capture_moves(player);
  }

  return new_board;
}

std::vector<Pos> Board::get_surrounding_positions(const Piece piece,
                                                  const Player neighbour) const {
  auto positions = std::vector<Pos>();
  auto add_if_valid = [this, &neighbour, &positions](Pos pos) {
    if (Pos::is_valid(pos) &&
        this->pieces[pos.get_index()].get_player() == neighbour) {
      positions.push_back(pos);
    }
  };

  auto pos = piece.get_pos();
  auto black_odd_row = piece.get_player() == Player::Black && pos.get_row() % 2;
  auto white_even_row =
      piece.get_player() == Player::White && pos.get_row() % 2 == 0;
  auto steps_forward = black_odd_row || white_even_row ? 5 : 3;
  auto steps_backward = black_odd_row || white_even_row ? 3 : 5;
  auto sign = piece.get_player() == Player::Black ? 1 : -1;

  add_if_valid(pos + (4 * sign));
  if (!pos.on_edge())
    add_if_valid(pos + (steps_forward * sign));
  if (piece.is_king())
    add_if_valid(pos + (4 * -sign));
  if (piece.is_king() && !pos.on_edge())
    add_if_valid(pos + (steps_backward * -sign));

  return positions;
}

void Board::perform_move(const Move& move) {
  auto piece = pieces[move.src.get_index()];
  assert(piece.get_player() == player_turn);
  piece.move(move.dst);
  pieces[move.dst.get_index()] = piece;
  pieces[move.src.get_index()] = Piece(move.src);
}

