#include "MyFrame.h"
// IDs for the controls
enum
{
	// IDs of File_menu
	Quit_Menu = wxID_EXIT,
	NewFile_Menu = 100,
	OpenFile_Menu,
	Save_Menu,
	SaveAs_Menu,

	// IDs of Edit_menu
	Undo_Menu = 200,
	Copy_Menu,
	Cut_Menu,
	Paste_Menu,

	// IDs of Help_menu
	Documentation_Menu = 300,
	About_Menu = wxID_ABOUT,

	TextCtrl_ID = 400
};

// event Tables macros
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	// File_menu
	EVT_MENU(NewFile_Menu, MyFrame::OnNewFile)
	EVT_MENU(OpenFile_Menu, MyFrame::OnOpenFile)
	EVT_MENU(Save_Menu, MyFrame::OnSave)
	EVT_MENU(SaveAs_Menu, MyFrame::OnSaveAs)
	EVT_MENU(Quit_Menu, MyFrame::OnExit)

	// Edit_menu
	EVT_MENU(Undo_Menu, MyFrame::OnUndo)
	EVT_MENU(Copy_Menu, MyFrame::OnCopy)
	EVT_MENU(Cut_Menu, MyFrame::OnCut)
	EVT_MENU(Paste_Menu, MyFrame::OnPaste)

	// Help_menu
	EVT_MENU(Documentation_Menu, MyFrame::OnDocumentation)
	EVT_MENU(About_Menu, MyFrame::OnAbout)

wxEND_EVENT_TABLE()

// the constructor
MyFrame::MyFrame(const wxString& title = "Text Editor", int posx = 100, int posy = 100, int sx = 800, int sy = 600): wxFrame(NULL, wxID_ANY, title, wxPoint(posx, posy), wxSize(sx, sy), 1)
{
	this->sizex = sx;
	this->sizey = sy;
	wxPanel *panel = new wxPanel(this, wxID_ANY);
	//wxButton *b1 = new wxButton(panel, B1_Button, "About", wxPoint(50, 50), wxDefaultSize);
	// create the menu bar
	controltxt = new wxTextCtrl(panel, TextCtrl_ID, "", wxPoint(0,0), wxSize(sizex, sizey), wxTE_MULTILINE);

	wxMenuBar *menuBar = new wxMenuBar();

	// File_menu
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(NewFile_Menu, "&New File \tCtrl-N","Create New file");
	fileMenu->Append(OpenFile_Menu, "&Open File\tCtrl-O", "Open an existing file");
	fileMenu->Append(Save_Menu, "&Save\tCtrl-S", "Save the current file");
	fileMenu->Append(SaveAs_Menu, "&Save As\tCtrl-Shift-S", "Save as the current file");
	fileMenu->Append(Quit_Menu, "&Exit\tCtrl-Q", "Quit the text editor");

	// Edit_menu
	wxMenu *editMenu = new wxMenu;
	editMenu->Append(Undo_Menu, "&Undo", "Go Back");
	editMenu->Append(Copy_Menu, "&Copy", "Copy selected text");
	editMenu->Append(Cut_Menu, "&Cut", "Cut selected text");
	editMenu->Append(Paste_Menu, "&Paste", "Paste the text");

	// Help_menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(Documentation_Menu, "&Documentation", "show the documentation");
	helpMenu->Append(About_Menu, "&About\tF1", "show about dialog");

	// append the created menu to the menu bar
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(editMenu, wxT("&Edit"));
	menuBar->Append(helpMenu, "&Help");

	// attach the menu bar to the frame
	SetMenuBar(menuBar);

	// status bar
	CreateStatusBar(2);
	SetStatusText("Status bar");

}

#include "wx/wfstream.h"
#include "wx/filedlg.h"
#include "wx/txtstrm.h"
#include "wx/textctrl.h"
//wxIMPLEMENT_CLASS(MyFrame, wxDocument);
// event handlers
// File_menu

void MyFrame::OnNewFile(wxCommandEvent& event)
{
	if(pathFile != ""){
		OnSave(event);
	}
	else 
	{
		OnSaveAs(event);
	}
	pathFile = "";
	currentText = " ";
	controltxt->SetValue(currentText);
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
	currentText = "";
	wxFileDialog 
		openFileDialog(this, ("Open txt file"), "","",
				"txt file (*.txt) |*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if( openFileDialog.ShowModal() == wxID_CANCEL)
			return; // the user changed idea
		//proceed loading the file chosen by the user
		wxFileInputStream input_stream(openFileDialog.GetPath());
		if( !input_stream.IsOk())
		{
			wxLogError("Cannot open the file '%s'.", openFileDialog.GetPath());
			return;
		}
		pathFile = openFileDialog.GetPath();
		wxTextInputStream text(input_stream, wxT("\x09"), wxConvUTF8);
		controltxt->SetValue(currentText);
		while(!input_stream.Eof())
		{
			wxString str = text.ReadLine();
			(*controltxt) << str <<'\n';
		}

		currentText = controltxt->GetValue();
		std::cout << "Path of the file : "<< pathFile<<std::endl;
///		(*controltxt) << "HELLO WORLD\n";
}

void MyFrame::OnSave(wxCommandEvent& event)
{
	currentText = controltxt->GetValue();
	if( pathFile != "")
	{
		wxFileOutputStream output_stream(pathFile);
		wxTextOutputStream text(output_stream);
		text << currentText;
	}
	else
		OnSaveAs(event);
	std::cout << "Path of the file : "<< pathFile<<std::endl;
}

void MyFrame::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, ("save txt file"), "", "", "txt file (*.txt) |*.txt", wxFD_SAVE);
	saveFileDialog.ShowModal(); // Important
	wxString str;
	str = controltxt->GetValue();
	pathFile = saveFileDialog.GetPath() + ".txt";
	wxFileOutputStream output_stream(pathFile);//saveFileDialog.GetPath() + ".txt");
	wxTextOutputStream text(output_stream);
	text << str;
	std::cout << "Path of the file : "<< pathFile<<std::endl;
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	if(pathFile == "")
		OnSaveAs(event);
	else
		OnSave(event);
	Close(true); // close the window
}

// Edit_menu
void MyFrame::OnUndo(wxCommandEvent& event)
{
	controltxt->SetValue(currentText);
}

void MyFrame::OnCopy(wxCommandEvent& event)
{
	currentText = controltxt->GetValue();
	selectedText = controltxt->GetStringSelection();
	std::cout<<selectedText<<std::endl;
}

void MyFrame::OnCut(wxCommandEvent& event)
{
	currentText = controltxt->GetValue();
	selectedText = controltxt->GetStringSelection();
	wxString temp = " ";
	controltxt->WriteText(temp);
}

void MyFrame::OnPaste(wxCommandEvent& event)
{
	currentText = controltxt->GetValue();
	if(selectedText != "")
		controltxt->WriteText(selectedText);
}

// Help_menu
void MyFrame::OnDocumentation(wxCommandEvent& event)
{}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(wxString::Format("This is basic text editor"), "About the app", 0, this);
}
