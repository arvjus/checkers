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
