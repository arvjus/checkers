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

#include <wx/wx.h>
#include <wx/generic/panelg.h>
#include <memory>
#include "game.h"

class MainFrame;
class BoardPanel : public wxPanel {
public:
  const static short WIDTH = 800, HEIGHT = 800;
  const static short ROWS = 8, COLS = 8;
  const static short SQUARE_SIZE = WIDTH / ROWS;
  const static short MARGIN = 2;

  BoardPanel(wxFrame* parent, const std::unique_ptr<Game>& g, const Pos& sel, const std::vector<Pos>& moves);

private:
  MainFrame& frame;
  wxBitmap black;
  wxBitmap black_sel;
  wxBitmap black_king;
  wxBitmap black_king_sel;
  wxBitmap white;
  wxBitmap white_sel;
  wxBitmap white_king;
  wxBitmap white_king_sel;
  wxBitmap valid_position;
  wxSize figure_offs;
  wxFont font;
  const std::unique_ptr<Game>& game;
  const Pos& selection;
  const std::vector<Pos>& valid_positions;

  void handlePaintEvent(wxPaintEvent& event);
  void handleKeyEvent(wxKeyEvent& event);
  void handleMouseEvent(wxMouseEvent& event);
};

