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

