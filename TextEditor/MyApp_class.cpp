#include "MyFrame.h"
#include "MyApp_class.h"

// implement the App
wxIMPLEMENT_APP(MyApp_class);

bool MyApp_class::OnInit()
{
	if( !wxApp::OnInit())
		return false;

	// create the main application window
	MyFrame *frame = new MyFrame("Text Editor", 100, 100, 800, 600);

	// show the frame
	frame->Show(true);

	// start the run loop
	return true;
}