// Dies ist die Haupt-DLL.

#include "stdafx.h"
#include <conio.h>
#include "CppArduFrame.h"
#include "CppFrame.h"

namespace CppArduDevelopmentFrame {

	int CppArduDevelopment::Main(void)
	{
	//	setup();
		for(;;)
		{
			if (_kbhit())
			{
				Serial._append((char)_getch());
			}
	//		loop();
		}
	}
}
