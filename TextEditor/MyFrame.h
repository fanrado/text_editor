#ifndef MyFrame_h
#define MyFrame_h
#include "wx/wx.h"

class MyFrame : public wxFrame
{
	public:
		MyFrame(const wxString& title, int posx, int posy, int sx, int sy);

		// events methods when a menu was clicked
		// File_menu
		void OnNewFile(wxCommandEvent& event);
		void OnOpenFile(wxCommandEvent&event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);

		// Edit_menu
		void OnUndo(wxCommandEvent& event);
		void OnCopy(wxCommandEvent& event);
		void OnCut(wxCommandEvent& event);
		void OnPaste(wxCommandEvent& event);

		// Help_menu
		void OnDocumentation(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		// button
		//void Onb1(wxCommandEvent& event);

	private:
		// the event table macro
		wxDECLARE_EVENT_TABLE();

		wxTextCtrl *controltxt;
		wxString selectedText = "";
		wxString currentText = "";

		int sizex, sizey;
		wxString pathFile = "";

};
#endif