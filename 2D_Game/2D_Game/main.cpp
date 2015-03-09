#define _AFXDLL
#include <SFML/Graphics.hpp>
#include "GameEngine.h"

#include "windows.h"

#using <mscorlib.dll>
#include <tchar.h>

using namespace System;

#using <System.Windows.Forms.dll>
using namespace System::Windows::Forms;

#using <System.dll>



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GameEngine ge;

	ge.run();

	return (0);
}