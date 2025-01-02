#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

using namespace CryptoNET;

[STAThread]
void main(array<String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Cipher^ c = gcnew Cipher();
	c->loadLibraries();
	CryptoNET::MainForm form;
	form.setCipher(c);
	form.loadInformation();
	Application::Run(% form);
}