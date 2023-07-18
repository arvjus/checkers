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

#include <wx/wx.h>
#include "main_frame.h"

class CheckersApp : public wxApp {
  bool OnInit() override {
    if (wxPlatformInfo::Get().GetOperatingSystemFamilyName() == "Macintosh") {
      wxImage::AddHandler(new wxPNGHandler);
    }
    (new MainFrame())->Show();
    return true;
  }
};

wxIMPLEMENT_APP(CheckersApp);
