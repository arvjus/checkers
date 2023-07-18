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

#include <wx/statbmp.h>
#include <checkers_config.h>
#include "board_panel.h"
#include "main_frame.h"

wxColour DARK{140, 140, 140};
wxColour LIGHT{230, 230, 230};
wxColour WHITE{250, 250, 250};

BoardPanel::BoardPanel(wxFrame* f, const std::unique_ptr<Game>& g, const Pos& sel, const std::vector<Pos>& moves) :
    wxPanel(f), frame(static_cast<MainFrame&>(*f)),
    black{ASSETS_DIR"/black.png",wxBITMAP_TYPE_PNG},
    black_sel{ASSETS_DIR"/black-sel.png", wxBITMAP_TYPE_PNG},
    black_king{ASSETS_DIR"/black-king.png", wxBITMAP_TYPE_PNG},
    black_king_sel{ASSETS_DIR"/black-king-sel.png", wxBITMAP_TYPE_PNG},
    white{ASSETS_DIR"/white.png", wxBITMAP_TYPE_PNG},
    white_sel{ASSETS_DIR"/white-sel.png", wxBITMAP_TYPE_PNG},
    white_king{ASSETS_DIR"/white-king.png", wxBITMAP_TYPE_PNG},
    white_king_sel{ASSETS_DIR"/white-king-sel.png", wxBITMAP_TYPE_PNG},
    valid_position{ASSETS_DIR"/valid-position.png", wxBITMAP_TYPE_PNG},
    figure_offs((SQUARE_SIZE - black.GetSize().GetWidth()) / 2, (SQUARE_SIZE - black.GetSize().GetHeight()) / 2),
    font{12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"},
    game(g), selection(sel), valid_positions(moves) {

  wxInitAllImageHandlers();

  Bind(wxEVT_PAINT, & BoardPanel::handlePaintEvent, this);
  Bind(wxEVT_CHAR, & BoardPanel::handleKeyEvent, this);
  Bind(wxEVT_LEFT_DOWN, & BoardPanel::handleMouseEvent, this);
  Bind(wxEVT_RIGHT_DOWN, & BoardPanel::handleMouseEvent, this);
}

void BoardPanel::handlePaintEvent(wxPaintEvent& event) {
  wxPaintDC dc(this);
  dc.SetBackground({DARK});
  dc.Clear();

  auto& board = game->get_board();

  Pos pos = 1;
  for (short row = 0; row < ROWS; row++)
    for (short col = row % 2; col < COLS; col += 2, pos ++) {
      wxPoint light_tile_pos{col * SQUARE_SIZE + MARGIN, row * SQUARE_SIZE + MARGIN};
      wxPoint dark_tile_pos{(col + (row % 2 ? -1 : 1)) * SQUARE_SIZE + MARGIN, row * SQUARE_SIZE + MARGIN};

      // light tile
      dc.SetBrush(LIGHT);
      dc.SetPen(*wxTRANSPARENT_PEN);
      dc.DrawRectangle(light_tile_pos, {SQUARE_SIZE, SQUARE_SIZE});

      // numbering
      dc.SetFont(font);
      dc.SetTextForeground(WHITE);
      dc.DrawText(wxString::Format("%d", (int)pos), dark_tile_pos.x + 4, dark_tile_pos.y + 2);

      // piece
      auto piece = board.get_piece_at_pos(pos);
      if (pos == selection) {
        if (piece.get_player() == Player::Black && piece.is_king())      dc.DrawBitmap(black_king_sel, dark_tile_pos);
        else if (piece.get_player() == Player::Black)                    dc.DrawBitmap(black_sel, dark_tile_pos);
        else if (piece.get_player() == Player::White && piece.is_king()) dc.DrawBitmap(white_king_sel, dark_tile_pos);
        else if (piece.get_player() == Player::White)                    dc.DrawBitmap(white_sel, dark_tile_pos);
      } else {
        if (piece.get_player() == Player::Black && piece.is_king())      dc.DrawBitmap(black_king, dark_tile_pos + figure_offs);
        else if (piece.get_player() == Player::Black)                    dc.DrawBitmap(black, dark_tile_pos + figure_offs);
        else if (piece.get_player() == Player::White && piece.is_king()) dc.DrawBitmap(white_king, dark_tile_pos + figure_offs);
        else if (piece.get_player() == Player::White)                    dc.DrawBitmap(white, dark_tile_pos + figure_offs);
      }
    }

  if (selection) {
    for (auto dst : valid_positions) {
      int row = (dst - 1) / 4;
      int col = 2 * ((dst - 1) % 4) + 1 - row % 2;
      wxPoint point{col * SQUARE_SIZE + MARGIN, row * SQUARE_SIZE + MARGIN};
      dc.DrawBitmap(valid_position, point + figure_offs);
    }
  }
}

void BoardPanel::handleKeyEvent(wxKeyEvent& event) {
  frame.handleKeyEvent(event);
}

void BoardPanel::handleMouseEvent(wxMouseEvent& event) {
  auto col = (event.GetPosition().x - MARGIN) / SQUARE_SIZE;
  auto row = (event.GetPosition().y - MARGIN) / SQUARE_SIZE;
  if (col % 2 != row % 2) {
    Pos pos = row * 4 + col / 2 + 1;
    frame.handleMouseClickOnPosition(pos);
  }
}
