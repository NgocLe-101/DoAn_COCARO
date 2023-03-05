#include <iostream>
#include "View.h"
#include "CONSTANT_VALUES.h"
#include "CONTROL.h"
#include "MODEL.h"
using namespace std;

int main()
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	FixConsoleWindow();
	StartGame();
	bool validEnter = true;
	while (true)
	{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) {
			ExitGame();
			return 1;
		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) {
				switch (CheckBoard(_X, _Y)) {
				case -1:
					SetColor(c_red);
					wcout << X_SYM;
					SetColor(c_def);
					break;
				case 1:
					SetColor(c_green);
					wcout << O_SYM;
					SetColor(c_def);
					break;
				case 0:
					validEnter = false;
				}
				
				if (validEnter) {
					int winner = ProcessFinish(TestBoard());
					switch (winner)
					{
					case -1:
					case 1:
					case 0:
						char c;
						do
						{
							c = AskContinue(winner);
						} while (c!='Y'&&c!='N');
						if (c == 'Y')
							StartGame();
						else {
							ExitGame();
							return 0;
						}
					}
				}
				validEnter = true;
			}
		}
	}
    return 0;
}


